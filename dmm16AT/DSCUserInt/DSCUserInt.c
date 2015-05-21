//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: DSCUserInt.c   v5.9
// Desc: Sample program that demonstrates how to use the User Interrupt function
// Created by 	KL
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
#define main DMM16ATDSCUserInt
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
DSCUSERINT dscuserint; // structure for setting user interrupt instead mode
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff;         // temp variable of size int
float floatBuff;     // temp variable of size float
int i;
long counter;	     // the global variable to be modified by the user defined function
long last_counter; // stores last value in counter

void count(void * param);   // user function

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. User interrupt setup
//	    IV. Trigger the interrupts (just for demo purposes)
//	     V. Cleanup
//
//=============================================================================

int main( void )
{
	//=========================================================================
	// I. DRIVER INITIALIZATION
	//
	//    Initializes the DSCUD library.
	//
	//	  Initialize the driver, using the driver version for validation
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

	printf("Enter the interrupt : ");
	scanf("%d", &intBuff);
	dsccb.int_level = (BYTE) intBuff;

	if(dscInitBoard(DSC_DMM16AT, &dsccb, &dscb)!= DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInitBoard error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// III. USER INT INITIALIZATION and Run
	//
	//		Sets up the following parameters for the user interrupt:
	//			user interrupt function
	//			interrupt source
	//			clock source (if the interrupt source is a counter/timer)
	//			interrupt rate (if the interrupt source is a counter/timer
	//	 				    and the clock source is internal)
	//
	//	Note : The user can also use dscCounterDirectSet() to set the
	//		 counter rate and then set rate = 0. The user is forced to use
	//		 dscCounterDirectSet() if rate = 0
	//=========================================================================

	// if using dscCounterDirectSet to specify the user rate then set
	// dscuserint.rate = 0.
	// For dscCounterDirectSet the parameters are specified as below :	
	// "BYTE dscCounterDirectSet( DSCCB, BYTE mode, WORD nDivider, BYTE counter)";
	//
	// dscCounterDirectSet(dscb, 0x34, 1000, 0);		
	//

	last_counter = 0;
	counter =0;		// set counter to 0
	
	// On DMM16AT, you have 1 choices for the interrupt source
	//								1 choices for the counter
	//								2 choices for the clksource :
	//
	//	intsource	counter		clksource		description
	//	0			0			0				counter0, 100KHz
	//	0			0			1				external counter

	// For simplicity alot of options are set for the user. When really
	// running please reset the options below.
	
	dscuserint.intsource = 0;
	dscuserint.counter = 0;
	dscuserint.rate = 1.1f;

	printf("Enter clock source (0 for internal, 1 for external) : ");
	scanf("%d", &intBuff);
	dscuserint.clksource = (BYTE) intBuff;
   
	printf("Enter the interrupt rate in hertz : ");
	scanf("%f", &floatBuff);
	dscuserint.rate = (FLOAT) floatBuff;

	if( (result = dscUserInt(dscb, &dscuserint, (DSCUserInterruptFunction)count)) != DE_NONE) 
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscUserInt error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//===========================================================================
	//	V. CASES FOR USERINT 
	//
	//      Tests userinterrupt
	//===========================================================================

	while( counter < 1024 )
	{
		printf("UserInt counter %ld, estimated rate %ld/sec\n", counter, (counter-last_counter));
		last_counter = counter;
		dscSleep(1000);
	}

	// must manually cancel interrupts
	if( (result = dscCancelOp(dscb)) != DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscCancelOp error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}
	dscClearUserInterruptFunction(dscb);  // clears user interrupt settings

	//=========================================================================
	// IV. CLEANUP
	//
	//	   Cleanup any remnants left by the program and free the resources used
	//	   by the driver.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. free the memory allocated for sample values
	//	   2. free the driver resources
	//=========================================================================

	dscFree();

	printf( "\nDSCUserInt completed.\n" );

	return 0;
} // end main()



//=============================================================================
//	The user interrupt routine
//
//	Note: If using DOS, you cannot execute dsc driver functions to access the board
//	both in the main program and in the user interrupt routine. This is because
//	the driver locks the board in the main program when it is being used so that
//	no other program can access it and interfere with a function while it is executing.
//	To access the board inside the interrupt routine in DOS, use direct I/O functions
//	( inp(addr), outp(addr,data) ).
//
//=============================================================================

void count(void * param)
{
	counter ++;
}


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
