//=============================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// DSCADAutoCal.c	v5.9
// Sample program that performs AD auto calibration and verification
// Created by KL
//=============================================================

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
// diamond driver includes
#include "../../../../current/dev/source/dscud.h"
#endif

// Linux and QNX
#if defined(linux) || defined(__QNXNTO__) || defined(_WRS_VXWORKS_5_X)
#include <stdlib.h>
#include <math.h>
#include <time.h>
// diamond driver includes
#include "dscud.h"

#ifdef _WRS_VXWORKS_5_X
#include <selectLib.h>
#define main DMM16ATDSCADAutoCal
#else
#include <sys/time.h>
#endif

#ifdef _WRS_VXWORKS_5_X
#include <selectLib.h>
#define main DMM16ATDSCADAutoCal
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
BYTE result; // returned error code
DSCB board;  // handle used to refer to the board
DSCCB dsccb; // structure containing board settings
WORD sample; // sample reading
DSCAUTOCAL dscautocal; // structure containing auto-calibration settings
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff; // temp variable of size int
int i;	     // miscellaneous counter


//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. AutoCal Settings Initialization
//	    IV. Auto-Calibration
//		 V. Calibration Verification
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
	//    STEPS TO FOLLOW:
	//
	//	  1. initialize the driver, using the driver version for validation
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
	//     STEPS TO FOLLOW:
	//
	//	   1. set the board type to DSC_DMM16 for DMM-16-AT board
	//	   2. set the base address (must be between 0x220-0x3E0)
	//	   3. set the interrupt level (must be between 3-15)
	//	   4. intialize and register the board with the driver, after which
	//		  the struct, dscb, now holds the handle for the board
	//=========================================================================

	printf( "\nDMM16AT BOARD INITIALIZATION:\n" );

	printf("Enter the base address (default 0x300) : ");
	scanf( "%hx", &dsccb.base_address );

	dsccb.int_level = 3;

	if(dscInitBoard(DSC_DMM16AT, &dsccb, &board)!= DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// III. AUTOCAL SETTINGS INITIALIZATION
	//
	//		Initialize the structure containing the AD autocal settings.
	//
	//		STEPS TO FOLLOW:
	//
	//		1. set the range code (must be between 0-15 or 255)
	//		2. set the use_eeprom flag to TRUE (unless you plan to write your
	//		   own reference voltages with the first use of the board -- see
	//		   the accompanying utility, MeasureReferences, for more details)
	//		3. set the boot adrange
	//=========================================================================

	/* PRE-FILLED EXAMPLE
	dscautocal.adrange = 0xFF;
	dscautocal.use_eeprom = (BYTE)TRUE;
	dscautocal.boot_adrange = 0;
	*/

	do {
		printf( "\n\nAUTOCAL SETTINGS INITIALIZATION:\n" );

		printf( "Enter the range to calibrate (0-15) or 255 to calibrate all ranges: " );
		scanf( "%d", &intBuff);
		dscautocal.adrange = (BYTE) intBuff;

		printf( "Enter the AD range the board should boot up in (0-15): " );
		scanf("%d", &intBuff);
		dscautocal.boot_adrange = (BYTE) intBuff;

		getchar();

	//=========================================================================
	// IV. AUTO-CALIBRATION
	//
	//	   Perform the actual AD auto-calibration of the board.
	//
	//	   STEPS TO FOLLOW:
	//
	//	   1. perform auto-calibration
	//=========================================================================

		printf( "\nAUTO-CALIBRATION:\n" );
		printf( "Starting AD auto-calibration...this will take a few seconds\n" );

		if( (result = dscADAutoCal( board, &dscautocal )) != DE_NONE )
	 	{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscADAutoCal error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
	 		return 0;
	 	}
    	printf( "Completed\n\n" );


	//=========================================================================
	// V. CALIBRATION VERIFICATION
	//
	//	  To verify that the auto-calibration was successfully completed, you
	//	  should run dscADCalVerify() on the 15 possible configuration modes to
	//	  ensure that the gain and offset errors meet a specified tolerance (2
	//	  in this example). You can obtain the possible combinations by writing
	//	  a for loop and bit-wise operations similar to those used below.
	//
	//	  NOTE: Before running dscADCalVerify(), you must remember to call the
	//			dscADSetSettings() function to change the board's AD settings
	//			to the next configuration mode to be tested.
	//
	//	  STEPS TO FOLLOW:
	//
	//	  1. set the range, polarity, and gain to the next combination of
	//	     values (loop will iterate through all 16 possible combinations)
	//	  2. set the load calibration settings flag to TRUE
	//	  3. set the current channel to 0
	//	  4. initialize the AD conversion with these settings
	//	  5. set the adrange to the current value of the counter
	//	  6. verify that the calibration was successful and output results
	//=========================================================================

		printf( "\nCALIBRATION VERIFICATION:\n" );

		for( i = 0; i < 16; i++ )
		{
			if ( ( i > 3 && i < 8 )  )
				continue;

			dscautocal.adrange = i;
			dscautocal.ad_gain = 0;
			dscautocal.ad_offset = 0;

			if( ( result = dscADCalVerify( board, &dscautocal ) ) != DE_NONE )
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscADCalVerify error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				return 0;
			}

			printf( "Configuration Mode: %d, Offset Error: %9.3f, Gain Error: %9.3f\n", i, dscautocal.ad_offset, dscautocal.ad_gain );

			if ( fabs( dscautocal.ad_offset ) > 2.0f ||
				 fabs( dscautocal.ad_gain ) > 2.0f )
				printf( "Value for offset or gain exceeded specified tolerance\n" );
			else printf( "Values for offset and gain met specified tolerance\n" );
		}

		printf("\nEnter 'q' to exit or press any key to continue : ");
	} while( getchar() != 'q');


	//=========================================================================
	// VI. CLEANUP
	//
	//	   Cleanup any remnants left by the program and free the resources used
	//	   by the driver.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. free the driver resources
	//=========================================================================

	dscFree();

	printf( "\nDSCADAutoCal completed. \n" );

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
