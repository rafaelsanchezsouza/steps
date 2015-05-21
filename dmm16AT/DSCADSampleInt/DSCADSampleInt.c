//=============================================================================                                                                                          //=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCADSampleInt.c   v5.9
// Desc: Sample program that demonstrates how to take an interrupt-based AD
//		 sample
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
#define main DMM16ATDSCADSampleInt
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

// macros defined
#define SLEEP_TIME 1000

// var declarations
BYTE result; // returned error code
DSCB dscb;   // handle used to refer to the board
DSCCB dsccb; // structure containing board settings
DSCS dscs;   // used for interrupts.
DSCAIOINT dscaioint;         // structure containing auto-calibration settings
DSCADSETTINGS dscadsettings; // structure containing A/D conversion settings
ERRPARAMS errorParams;       // structure for returning error code and error string
DFLOAT voltage;
int intBuff;     // temp variables of size int
long  longBuff;  // temp variables of size long
float floatBuff; // temp variables of size float
int i;	         // miscellaneous counter

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. Interrupt Settings
//	    IV. Interrupt
//		 V. Data check
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

	printf("Enter the interrupt level (3-15) : ");
	scanf("%d", &intBuff);
	dsccb.int_level = (BYTE) intBuff;

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
	// IV. I/O INTERRUPT SETTINGS INITIALIZATION
	//
	//	   Initialize the structure containing the analog I/O interrupt
	//	   settings.
	//
	//	   NOTE: You must allocate space for the buffer holding the returned
	//		     sample values. Also, be generous in allocating storage.
	//			 Allocating insufficient memory to hold sample data will result
	//			 in improper behavior of the driver, such as hanging interrupt
	//			 operations or assertion errors.
	//=========================================================================
	
	/* Prefilled example
	dscaioint.num_conversions = 1024;
	dscaioint.conversion_rate = 1000;
	dscaioint.cycle = (BYTE)FALSE;
	dscaioint.internal_clock = (BYTE)TRUE;
	dscaioint.low_channel = 0;
	dscaioint.high_channel = 3;
	dscaioint.external_gate_enable = (BYTE)FALSE;
	dscaioint.internal_clock_gate = (BYTE)FALSE;
	dscaioint.fifo_enab = (BYTE)TRUE;
	dscaioint.fifo_depth = 256;
	dscaioint.dump_threshold = 0;
	*/

	printf( "\nI/O INTERRUPT SETTINGS INITIALIZATION\n" );

	memset(&dscaioint, 0, sizeof(DSCAIOINT));

	printf( "Enter the number of conversions (must be a multiple of FIFO depth) : " );
	scanf("%ld", &longBuff);
	dscaioint.num_conversions = (DWORD) longBuff;

	printf( "Enter the conversion rate in Hz (must be less than 100000) : " );
	scanf("%f", &floatBuff);
	dscaioint.conversion_rate = (FLOAT) floatBuff;

	printf( "Enter the cycle flag (0 for FALSE, 1 for TRUE) : " );
	scanf("%d", &intBuff);
	dscaioint.cycle = (BOOL) intBuff;

	printf( "Enter the internal clock flag (0 for FALSE, 1 for TRUE) : " );
	scanf("%d", &intBuff);
	dscaioint.internal_clock  = (BOOL) intBuff;

	printf( "Enter the lowest channel in the scan range (0-15) : " );
	scanf("%d", &intBuff);
	dscaioint.low_channel = (BYTE) intBuff;

	printf( "Enter the highest channel in the scan range (0-15) : " );
	scanf("%d", &intBuff);
	dscaioint.high_channel = (BYTE) intBuff;

	dscaioint.external_gate_enable = 0; // can enable it if need be

	dscaioint.internal_clock_gate = 0;   // can enable it if need be

	printf( "Enter the FIFO enable flag (0 for FALSE, 1 for TRUE) : " );
	scanf("%d", &intBuff);
	dscaioint.fifo_enab = (BOOL) intBuff;

	dscaioint.fifo_depth = 256;

	printf("Enter the dump threshold ( must be less or equal to num conversions ) : ");
	scanf("%ld", &longBuff);
	dscaioint.dump_threshold = longBuff;

	dscaioint.sample_values = (DSCSAMPLE*)malloc( sizeof(DSCSAMPLE) * dscaioint.num_conversions );

	getchar();

	//=========================================================================
	// V. I/O INTERRUPT SETTINGS INITIALIZATION
	//
	//	   Initialize the structure containing the analog I/O interrupt
	//	   settings.
	//
	//	   NOTE: You must allocate space for the buffer holding the returned
	//		     sample values. Also, be generous in allocating storage.
	//			 Allocating insufficient memory to hold sample data will result
	//			 in improper behavior of the driver, such as hanging interrupt
	//			 operations or assertion errors.
	//
	//=========================================================================

	printf( "\nSAMPLING AND OUTPUT\n" );

	do
	{
		if( ( result = dscADSampleInt( dscb, &dscaioint ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscADSampleInt error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			free( dscaioint.sample_values ); // remember to deallocate malloc() memory
			return 0;
		}

		dscs.transfers = 0;
		dscs.overflows = 0;
		dscs.op_type = OP_TYPE_INT;

		do{
			dscSleep(SLEEP_TIME);
			dscGetStatus(dscb,&dscs);
			printf("FIFO Overflows %lu, A/D Int Trans in progress: %lu Total Transf %lu\n", dscs.overflows, dscs.transfers, dscs.total_transfers);
		} while (dscs.op_type != OP_TYPE_NONE && !kbhit());

		// cancel interrupts manually for recycled mode or if interrupts are still running
		if( dscs.op_type != OP_TYPE_NONE)
		{
			if( (result = dscCancelOp(dscb)) != DE_NONE)
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscCancelOp error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				free( dscaioint.sample_values ); // remember to deallocate malloc() memory
				return 0;
			}
		}

		printf( "\nSample readouts:" );

		for( i = 0; i < (dscaioint.high_channel-dscaioint.low_channel + 1); i++)
			printf( " %hd", dscaioint.sample_values[i] );

		printf( "\n\nActual voltages:" );

		for(i = 0; i < (dscaioint.high_channel-dscaioint.low_channel + 1); i++)
		{
			if( dscADCodeToVoltage(dscb, dscadsettings, dscaioint.sample_values[i], &voltage) != DE_NONE)
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscADCodeToVoltage error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				free(dscaioint.sample_values);
				return 0;
			}
			printf( " %5.3lfV", voltage );
		}

		printf( "\n\n" );
		printf("Enter 'q' to exit, any key to continue\n");
	}
	while(getchar() != 'q');

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

	free( dscaioint.sample_values );

	dscFree();

	printf( "\nDSCADSampleInt completed.\n" );

	return 0;
} // end main()


#ifdef _WIN32_WCE
int WINAPI WinMain(	HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPTSTR    lpCmdLine,
					int       nCmdShow)
{
	printf("For users running cycled mode: to EXIT, hold down the 'q' key\n");
	printf("on the keyboard then press 'Enter' when 'q' letters appear on screen\n\n");
	main();

	return 0;
}

#endif
