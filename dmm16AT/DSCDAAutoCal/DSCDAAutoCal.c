//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCDAAutoCal.c  v5.9
// Desc: Sample program that demonstrates how to DA calibrate the board
// Created by KL
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
#define main DMM16ATDSCDAAutoCal
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
DSCB dscb;   // handle used to refer to the board
DSCCB dsccb; // structure containing board settings
DSCADSETTINGS dscadsettings;    // structure containing A/D conversion settings
DSCDACALPARAMS dscdacalparams;  // structure containing auto-calibration settings
ERRPARAMS errorParams;          // structure for returning error code and error string
int intBuff;     // temp variable of size int
float floatBuff; // temp variable of size float
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

	if( ( result = dscInit( DSC_VERSION ) ) != DE_NONE )
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
	//	   1. set the board type to DSC_DMM16AT for DMM-16-AT board
	//	   2. set the base address 
	//	   3. set the interrupt level
	//	   4. intialize and register the board with the driver, after which
	//		  the struct, dscb, now holds the handle for the board
	//=========================================================================

	/* PRE-FILLED EXAMPLE
	dsccb.boardtype = DSC_DMM16AT;
	dsccb.base_address = 0x300;
	dsccb.int_level = 5;
	dsccb.dma_level = 1;
	dsccb.clock_freq = 10000000;
	*/

	printf( "BOARD INITIALIZATION:\n" );

	printf("Enter the base address (default 0x300) : ");
	scanf( "%hx", &dsccb.base_address );

	dsccb.int_level = 3;

	if( ( result = dscInitBoard( DSC_DMM16AT, &dsccb, &dscb ) ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	//III. AUTOCAL SETTINGS INITIALIZATION
	//
	//		Initialize the structure containing the DA autocal settings. The
	//		structure element, dscautocal.darange, contains a code ranging from
	//		0-65535, that scales to a voltage based on the following formula:
	//
	//		Voltage = darange / 6553.5;
	//
	//		STEPS TO FOLLOW:
	//
	//		1. set the DA range code
	//		2. set the programmable voltage
	//=========================================================================

	printf( "\nAUTOCAL SETTINGS INITIALIZATION:\n" );

	/* PRE-FILLED EXAMPLE
	dscautocal.darange = 1000;
	*/

	memset(&dscdacalparams, 0, sizeof(DSCDACALPARAMS));

	printf( "Enter the DA range code 0 being fixed or \na float between 0-10.0 being the voltage : " );
	scanf("%f", &floatBuff);
	dscdacalparams.darange = (FLOAT) floatBuff;

	//=========================================================================
	// IV. AUTO-CALIBRATION
	//
	//	   Perform the actual DA auto-calibration of the board.
	//
	//	   STEPS TO FOLLOW:
	//
	//	   1. perform auto-calibration
	//=========================================================================

	printf( "\nAUTO-CALIBRATION:\n" );
	printf( "Starting DA auto-calibration...\n" );

	if( ( result = dscDAAutoCal( dscb, &dscdacalparams ) ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscDAAutoCal error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// V. CALIBRATION VERIFICATION
	//
	//	  To verify that the auto-calibration was successfully completed, you
	//	  should run dscDACalVerify() to ensure that the gain and offset errors
	//	  meet a specified tolerance (2 in this example).
	//
	//	  STEPS TO FOLLOW:
	//
	//	  1. verify that the calibration was successful and output results
	//=========================================================================

	printf( "\nCALIBRATION VERIFICATION:\n" );

	if( ( result = dscDACalVerify( dscb, &dscdacalparams ) ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscDACalVerify error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	printf( "Offset Error: %f, Gain Error: %f\n", dscdacalparams.offset, dscdacalparams.gain ); 

	if ( fabs( dscdacalparams.offset ) > 2.0 || 
		 fabs( dscdacalparams.gain ) > 2.0 )
		printf( "Value for offset or gain exceeded specified tolerance\n" );
	else printf( "Values for offset and gain met specified tolerance\n" );

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

	printf( "\nDSCDAAutoCal completed.\n" );

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
