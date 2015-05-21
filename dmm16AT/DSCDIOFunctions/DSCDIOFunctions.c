//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCDIOFunctions.c   v5.9
// Desc: Sample program that demonstrates how to use the digital I/O functions
// Created by	KL
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
#define main DMM16ATDSCDIOFunctions
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
BYTE result;   // returned error code
DSCB dscb;     // handle used to refer to the board
DSCCB dsccb;   // structure containing board settings
BYTE port;     // port used for digital I/O
BYTE output_b; // BYTE to output digital value
BYTE input_b;  // BYTE to input digital value
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff;   // temp variables of size int

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. DIO Input and Output
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

	dsccb.int_level = 5;

	if(dscInitBoard(DSC_DMM16AT, &dsccb, &dscb)!= DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	getchar();

	//=========================================================================
	// III. DIO INPUT AND OUTPUT
	//
	//		Perform a set of byte-level inputs and outputs. We start by sending
	//		an output byte value of 0 to the selected digital I/O port and then
	//		read from that same port again to verify that the correct value was
	//		exchanged. For word and bit-level operations, the steps are nearly
	//		identical with a few minor changes to function names and the size
	//		of the data to be transferred.
	//
	//		NOTE: Remember that the bytes received from port are supposed to be
	//			  equal to the inversion of the bytes sent. That is, the input
	//			  bytes are equal to 255 minus the output bytes.
	//
	//=========================================================================

	printf( "\nDIO INPUT AND OUTPUT:\n" );

	do
	{
		port = 0; // DMM-16-AT has only 1 DIO TTL port with 8 bits

		printf("Enter the value to port : ");
		scanf("%d", &intBuff);
		output_b = (BYTE) intBuff;

		if( ( result = dscDIOOutputByte( dscb, port, output_b ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscDIOOutputByte error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			return 0;
		}

		if( ( result = dscDIOInputByte( dscb, port, &input_b ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscDIOInputByte error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			return 0;
		}

		printf( "Byte value sent to port: %d, Byte value received from port: %d\n", (int)output_b, (int)input_b );
		printf("\nPress q to exit or ENTER to continue \n");
	}while( getchar() != 'q' );
	
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

	printf( "\nDSCDIOFunctions completed.\n" );

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
