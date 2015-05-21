//=============================================================================
//(c) Copyright 2005 Diamond Systems Corporation. Use of this source code
//is subject to the terms of Diamond Systems' Software License Agreement.
//Diamond Systems provides no warranty of proper performance if this
//source code is modified.
//
// File: DSCSetUserInt.c   v5.9
// Desc: Sample program that demonstrates how to use the User Interrupt functions
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
#include <mem.h>
#include <string.h>
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
#define main DMM16ATDSCSetUserInt
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
DSCS dscs;   // used for obtaining interrupt status.
DSCAIOINT dscaioint;		    // AD interrupt structure
DSCADSETTINGS dscadsettings;	// AD settings structure
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff;           // temp variable of size int
long  longBuff;        // temp variable of size long
float floatBuff;       // temp variable of size float

DSCUSERINTFUNCTION dscuserintfunc;  // structure for user interrupt setup
int counter;	 // variable to be modified by the user defined function

DFLOAT voltage;
int i; // temp variable

void count(void * param);		// user function

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//		III. Setup UserInt
//		IV. Setupt AD Int
//		V. Trigger Interrupt
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

	//=============================================================================
	// III. Setup User Interrupts
	//
	//		1. Specify the user interrupt function ( make sure you have a function 
	//			pointer already )
	//		2. Assign the mode to either USER_INT_AFTER or USER_INT_INSTEAD
	//		3. Set the userinterrupt values
	//
	//=============================================================================

	counter =0;      // set counter to 0
	dscuserintfunc.func = count; // assigning user function to function pointer
	dscuserintfunc.int_mode = USER_INT_AFTER;
	if( dscSetUserInterruptFunction( dscb, &dscuserintfunc) != DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscSetUserInterruptFunction error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//==============================================================================
	// IV. Setupt the other interrupt you want to run
	//		
	//		1. Setup any interrupt/counter timer funciton ( in this case, sampleInt)
	//
	//==============================================================================

	/////////////////////
	// setupt ad settings
	/////////////////////
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


	//////////////////////
	// setupt interrupt //
	//////////////////////
	printf( "\nI/O INTERRUPT SETTINGS INITIALIZATION\n" );

	memset(&dscaioint, 0, sizeof(DSCAIOINT));

	printf( "Enter the number of conversions (must be a multiple of FIFO depth) : " );
	scanf("%ld", &longBuff);
	dscaioint.num_conversions = (DWORD)longBuff;

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

	dscaioint.dump_threshold = 0;

	// allocate space for array to store ad values
	dscaioint.sample_values = (DSCSAMPLE*)malloc( sizeof( DSCSAMPLE ) * dscaioint.num_conversions );

	//============================================================================
	// V. SAMPLING AND OUTPUT
	//
	//		1. See the results of userinterrupt/user function and the regular interrupt
	//============================================================================

	printf( "\nSAMPLING AND OUTPUT\n" );

	while ( !kbhit() )
	{
		// start interrupt
		if( ( result = dscADSampleInt( dscb, &dscaioint ) ) != DE_NONE )
		{
			dscGetLastError(&errorParams);
			fprintf( stderr, "dscADSampleInt error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
			free( dscaioint.sample_values ); // remember to deallocate malloc() memory
			return 0;
		}
	
		// check status of interrupt
		dscs.transfers = 0;
		dscs.overflows = 0;
		dscs.op_type = OP_TYPE_INT;

		do{
			dscGetStatus(dscb,&dscs);
			dscSleep(SLEEP_TIME);
			printf("Fifo Overflows %lu, A/D Int Trans in progress: %lu, Total Trans %lu\n", dscs.overflows, dscs.transfers, dscs.total_transfers);
			printf("UserInt counter %d\n", counter);
		}while (dscs.op_type != OP_TYPE_NONE && !kbhit()) ;
	
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
	
		// print out AD code and convert ad code to voltage
		for( i = dscaioint.low_channel; i < dscaioint.high_channel + 1; i++)
			printf( " %hd", dscaioint.sample_values[i] );
	
		printf( "\nActual voltages:" );

		for( i = dscaioint.low_channel; i < dscaioint.high_channel + 1; i++)
		{
			if( dscADCodeToVoltage(dscb, dscadsettings, dscaioint.sample_values[i], &voltage) != DE_NONE)
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscADCodeToVoltage error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				free(dscaioint.sample_values);
				return 0;
			}

			printf( " %5.3lfV", voltage);
		}

		printf( "\n\n" );
		printf("Enter q to quit or any key to continue\n");
	}while(getchar() != 'q');

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

	dscuserintfunc.func = NULL;			          // set function pointer to null 
	dscuserintfunc.int_mode = USER_INT_CANCEL;	  // clear userinterrupt settings
	if( dscSetUserInterruptFunction(dscb, &dscuserintfunc) != DE_NONE)
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscSetUserInterruptFunction error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	dscFree();

	printf( "\nDSCSetUserInt completed.\n" );

	return 0 ;
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
	printf("For users running cycled mode: to EXIT, hold down the 'q' key\n");
	printf("on the keyboard then press 'Enter' when 'q' letters appear on screen\n\n");
	main();

	return 0;
}

#endif
