//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCADScan.c   v5.9
// Desc: Sample program that demonstrates how to perform an AD scan
// Created By KL
//=============================================================================

#include <stdio.h>

#ifdef _WIN32
#ifndef _WIN32_WCE
#include <conio.h>
#endif

#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// diamond driver includes
#include "dscud.h"
#endif


#ifdef _WIN32_WCE

#include <string.h>
#include <Winsock2.h>

static int kbhit()
{
	int i;
	int result=0;

	
	result |= GetAsyncKeyState(VK_RETURN);
	result |= GetAsyncKeyState(VK_SPACE);

	if (result != 0)
	{
		getchar();
		return 1;
	}

	//number keys, 0-9
	for (i=48; i<=57; i++)
		result |= GetAsyncKeyState(i);

	if (result != 0)
	{
		getchar();
		return 1;
	}

	//capital character keys, A-Z
	for (i=65; i<=90; i++)
		result |= GetAsyncKeyState(i);

	if (result != 0)
	{
		getchar();
		return 1;
	}

	//lower case keys, a-z
	for (i=97; i<=122; i++)
		result |= GetAsyncKeyState(i);

	if (result != 0)
	{
		getchar();
		return 1;
	}

	return result;
}

#endif


// DOS
#ifdef __BORLANDC__
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <mem.h>
// diamond driver includes
#include "../../../../current/dev/source/dscud.h"
#endif

// Linux and QNX
#if defined(linux) || defined(__QNXNTO__) || defined(_WRS_VXWORKS_5_X)
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
// diamond driver includes
#include "dscud.h"


#ifdef _WRS_VXWORKS_5_X
#include <selectLib.h>
#define main DMM16ATDSCADScan
#else
#include <sys/time.h>
#endif

static int kbhit()
{
	struct timeval timeout;
	fd_set rfds;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	FD_ZERO(&rfds);
	FD_SET(0, &rfds);

	if ( select(0+1, &rfds, NULL, NULL, &timeout) > 0 )
		return getchar();

	return 0;
}
#endif

// var declarations
BYTE result;    // returned error code
DSCB dscb;      // handle used to refer to the board
DSCCB dsccb;    // structure containing board settings
DFLOAT voltage; // actual voltage
DSCSAMPLE* samples;          // sample readings
DSCADSCAN dscadscan;         // structure containing A/D scan settings
DSCADSETTINGS dscadsettings; // structure containing A/D conversion settings
ERRPARAMS errorParams;       // structure for returning error code and error string
int intBuff;    // temp variable of size int
int i;          // miscellaneous counter

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//     STEPS TO FOLLOW:
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. AD Settings Initialization
//		IV. AD Scan Initialization
//	     V. Scanning and Output
//	    VI. Cleanup
//
//=============================================================================

int main( void )
{

	//=========================================================================
	// I. DRIVER INITIALIZATION
	//
	//    Initializes the DSCUD library.
	//
	//=========================================================================

	if( dscInit( DSC_VERSION ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInit error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// II. BOARD INITIALIZATION
	//
	//	   Initialize the DMM-16-AT board. This function passes the various
	//	   hardware parameters to the driver and resets the hardware.
	//
	//=========================================================================

	printf( "\nDMM16AT BOARD INITIALIZATION:\n" );

	printf("Enter the base address (default 0x300) : ");
  	scanf( "%hx", &dsccb.base_address );

	dsccb.int_level = 3;

	if(dscInitBoard(DSC_DMM16AT, &dsccb, &dscb)!= DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// III. AD SETTINGS INITIALIZATION
	//
	//	    Initialize the structure containing the AD conversion settings and
	//		then pass it to the driver.
	//
	//=========================================================================

	/* PRE-FILLED EXAMPLE
	dscadsettings.range = RANGE_10;
	dscadsettings.polarity = BIPOLAR;
	dscadsettings.gain = GAIN_1;
	dscadsettings.load_cal = (BYTE)TRUE;
	dscadsettings.current_channel = 0;
	*/

	printf( "\nAD SETTINGS INITIALIZATION\n" );

	memset(&dscadsettings, 0, sizeof(DSCADSETTINGS));

	printf( "Enter the range (0 for 5V range, 1 for 10V range): " );
	scanf("%d", &intBuff);
	dscadsettings.range = (BYTE) intBuff;

	printf( "Enter the polarity (0 for BIPOLAR, 1 for UNIPOLAR): " );
	scanf("%d", &intBuff);
	dscadsettings.polarity = (BYTE) intBuff;

	printf( "Enter the gain (0 for GAIN 1, 1 for GAIN 2, 2 for GAIN 4, 3 for GAIN 8): " );
	scanf("%d", &intBuff);
	dscadsettings.gain = (BYTE) intBuff;

	printf( "Enter the load calibration flag (0 for FALSE, 1 for TRUE): " );
	scanf("%d", &intBuff);
	dscadsettings.load_cal = (BYTE) intBuff;

	dscadsettings.current_channel = 0;

	if( ( result = dscADSetSettings( dscb, &dscadsettings ) ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscADSetSettings error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// IV. AD SCAN INITIALIZATION
	//
	//	   Initialize the structure containing the AD scan setting and allocate
	//	   memory for our buffer containing sample values.
	//
	//=========================================================================

	/* PRE-FILLED EXAMPLE
	dscadscan.low_channel = 3;
	dscadscan.high_channel = 6;
	dscadscan.gain = GAIN_1;
	*/

	printf( "\nAD SCAN INITIALIZATION\n" );

	memset(&dscadscan, 0, sizeof(DSCADSCAN));

	printf( "Enter the lowest channel in the scan range (0-15): " );
	scanf("%d", &intBuff);
	dscadscan.low_channel = (BYTE) intBuff;

	printf( "Enter the highest channel in the scan range (0-15): " );
	scanf("%d", &intBuff);
	dscadscan.high_channel = (BYTE) intBuff;

	dscadscan.gain = dscadsettings.gain;

	// allocate memory for buffer
	samples = (DSCSAMPLE*)malloc( sizeof(DSCSAMPLE) * ( dscadscan.high_channel - dscadscan.low_channel + 1 ) );

	getchar();

	//=========================================================================
	// V. SCANNING AND OUTPUT
	//
	//    Perform the actual sampling and then output the results. To calculate
	//	  the actual input voltages, we must convert the sample code (which
	//	  must be cast to a short to get the correct code) and then plug it
	//	  into one of the formulas located in the manual for your board (under
	//	  "A/D Conversion Formulas").
	//=========================================================================

	printf( "\nSCANNING AND OUTPUT\n" );

	do
	{
		if( ( result = dscADScan( dscb, &dscadscan, samples ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscADScan error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			free( samples ); // remember to deallocate malloc() memory
			return 0;
		}

		printf( "\nSample readouts:" );

		for( i = 0; i < (dscadscan.high_channel - dscadscan.low_channel)+ 1; i++)
			printf( " %hd", dscadscan.sample_values[i] );

		printf( "\n\nActual voltages:" );

		for( i = 0; i < (dscadscan.high_channel - dscadscan.low_channel)+ 1; i++)
		{
			if( dscADCodeToVoltage(dscb, dscadsettings, dscadscan.sample_values[i], &voltage) != DE_NONE)
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscInit error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				free(samples);
				return 0;
			}

			printf(" %5.3lfV", voltage);
		}

		printf( "\n" );
		printf("Enter 'q' to exit, any key to continue\n");
	}
	while (getchar() != 'q' );

	//=========================================================================
	// VI. CLEANUP
	//
	//	   Cleanup any remnants left by the program and free the resources used
	//	   by the driver.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. free the memory allocated for sample values
	//	   2. free the driver resources
	//=========================================================================

	free(samples);
	
	dscFree();

	printf( "\nDSCADScan completed.\n" );

	return 0;
} // end main()


#ifdef _WIN32_WCE
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	main();

	return 0;
}

#endif
