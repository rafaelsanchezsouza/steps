//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCDAConvert.c   v5.9
// Desc: Sample program that demonstrates how to perform a DA conversion
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
#define main DMM16ATDSCDAConvert
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
BYTE result;  // returned error code
DSCB dscb;    // handle used to refer to the board
DSCCB dsccb;  // structure containing board settings
BYTE channel; // selected output channel
DWORD output_code;     // DA code for desired output voltage
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff;  // temp variable of size int
int i;        // miscellaneous counter

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
//	   III. DA Conversion and Output
//	    IV. Cleanup
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
	//	   1. set the board type to DSC_DMM16AT for DMM-16-AT board
	//	   2. set the base address
	//	   3. set the interrupt level
	//	   4. intialize and register the board with the driver, after which
	//		  the struct, dscb, now holds the handle for the board
	//=========================================================================

	printf( "\nDMM16AT BOARD INITIALIZATION:\n" );

	printf("Enter the base address (default 0x300) : ");
	scanf( "%hx", &dsccb.base_address );

	dsccb.int_level = 5;

	if(dscInitBoard(DSC_DMM16AT, &dsccb, &dscb)!= DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	getchar();

	//=========================================================================
	// III. DA CONVERSION AND OUTPUT
	//
	//	    Perform the actual DA conversion, then take an AD sample to verify
	//	    and output the results. Note that in order to verify the conversion
	//	    process on a particular output channel, we must set the input
	//	    channel on the AD conversion to (Output Channel + 4). To calculate
	//	    the output code to obtain a particular input voltage, we must use
	//	    one of the formulas located in the manual for your board (under the
	//	    the section, "Generating an Analog Output"). For example, the
	//	    formula for bipolar mode is:
	//
	//	    Output code = Output Voltage / Full-Scale Voltage * 2048 + 2048
	//
	//	    To calculate the actual input voltages from sample codes, we must
	//	    convert the sample code (which must be cast to a short to get the
	//	    correct code) and then plug it into one of the formulas located in
	//	    the manual for your board (under "A/D Conversion Formulas"). For
	//	    example, if you are using a bipolar input range and 32-bit signed
	//	    integers:
	//
	//	    Input voltage = (AD Code / 32768) x Full-Scale Voltage
	//
	//	    STEPS TO FOLLOW:
	//
	//	    1. set the channel (must be between 0-1)
	//	    2. set the output code
	//	    3. write the output value to the selected output channel
	//	    4. repeat step 3 until a key is pressed
	//=========================================================================

	/* PRE-FILLED EXAMPLE
	channel = 0;
	output_code = 2048;
	*/

	do 
	{
		printf( "\nDA CONVERSION AND OUTPUT\n" );
	
		printf( "Enter the channel (0-3): " );
		scanf("%d", &intBuff);
		channel = (BYTE) intBuff;

		printf( "Enter the output code: " );
		scanf("%d", &intBuff);
		output_code = (DWORD)intBuff;

		printf( "\nSending output code, %d, to channel %d...\n", (int)output_code, channel );

		if( ( result = dscDAConvert( dscb, channel, output_code ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscDAConvert error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			return 0;
		}
		
		printf("Press q to quit or ENTER to continue ");
		
	}while(getchar() != 'q');

	//=========================================================================
	// IV. CLEANUP
	//
	//	   Cleanup any remnants left by the program and free the resources used
	//	   by the driver.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. free the driver resources
	//=========================================================================

	dscFree();

	printf( "\nDSCDAConvert completed.\n" );

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
