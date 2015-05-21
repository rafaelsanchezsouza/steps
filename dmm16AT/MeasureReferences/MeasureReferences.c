//=============================================================================
// (c) Copyright 2005 Diamond Systems Corporation. Use of this source code
// is subject to the terms of Diamond Systems' Software License Agreement.
// Diamond Systems provides no warranty of proper performance if this
// source code is modified.
//
// File: MeasureReferences.c  v5.9
// Desc: Sample program that demonstrates how to measure and set the reference
//       voltages in the EEPROM of your board
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
#define main DMM16ATMeasureReferences
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
ERRPARAMS errorParams; // structure for returning error code and error string
int intBuff;           // temp variable of size int
int menu;
int i;	// miscellaneous counter
DFLOAT refs[7];

//=============================================================================
// Name: main()
// Desc: Starting function that calls the driver functions used
//
//		 NOTE: By convention, you should capture the BYTE return value for each
//		 driver API call, and check the error code.
//
//	     I. Driver Initialization
//	    II. Board Initialization
//	   III. Measure References
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

	if( ( result = dscInit( DSC_VERSION ) ) != DE_NONE )
	{
		dscGetLastError(&errorParams);
		fprintf( stderr, "dscInit error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
		return 0;
	}

	//=========================================================================
	// II. BOARD INITIALIZATION
	//
	//	   Initialize the DMM-16AT board. This function passes the various
	//	   hardware parameters to the driver and resets the hardware.
	//
	//     STEPS TO FOLLOW:
	//
	//	   1. set the board type to DSC_DMM16AT for DMM-16AT board
	//	   2. set the base address
	//	   3. set the interrupt level (must be between 3-15)
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

	printf("\n");
	getchar();

	//=========================================================================
	// III. MEASURE REFERENCES
	//
	//		Measure the reference voltages for your board and then mention how
	//		to store these values in the EEPROM.
	//
	//		STEPS TO FOLLOW:
	//
	//		1. wait for the user to attach the voltmeter ground probe to the negative
	//		   pin and the other probe to the positive pin located at J9 on the board
	//		2. allocate memory for the reference voltages
	//		3. enable the selected channels for calibrate
	//		4. measure the voltage on the current channel
	//		5. repeat steps 3-4 for channels 0-5
	//		6. run dscAutoCal to write the values to the EEPROM
	//=========================================================================


	do {
		printf("\nSelect from the following menu \n");
		printf("0) Exit\n");
		printf("1) EEProm dump \n");
		printf("2) Measure reference voltage \n");

		scanf("%d", &menu);

		if( menu == 0)
			break;
		else if( menu == 1)
		{
			if( dscGetReferenceVoltages( dscb, refs) != DE_NONE )
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscGetReferenceVoltage error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				return 0;
			}

			for( i = 0; i < 5 ; i++)
			{
				printf("The Stored Reference Voltage %lf\n", refs[i]);
			}
		}
		else if( menu == 2)
		{

			printf( "Locate J7 on the DMM16AT. Place the ground probe of your voltmeter\non the G pin and the other probe \non the M pin, then press any key.\n" );
			getchar();
         
			dscSetCalMux(dscb, 1);

			for( i = 0; i < 5; i++ )
			{
				if( dscADSetChannel(dscb, (unsigned char) i, (unsigned char)i) != DE_NONE )
				{
					dscGetLastError(&errorParams);
					fprintf( stderr, "dscADSetChannel error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
					return 0;
				}

				printf( "Enter the voltage on the voltmeter (cal mux channel %d): ", i );
				scanf( "%lf", &refs[i] );
			}

			dscSetCalMux(dscb, 0);

			if( dscSetReferenceVoltages( dscb, refs) != DE_NONE )
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscSetReferenceVoltage error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				return 0;
			}

			for( i =0; i < 5; i++)
				refs[i] =0;

			if( dscGetReferenceVoltages( dscb, refs) != DE_NONE )
			{
				dscGetLastError(&errorParams);
				fprintf( stderr, "dscGetReferenceVoltage error: %s %s\n", dscGetErrorString(errorParams.ErrCode), errorParams.errstring );
				return 0;
			}

			for( i = 0; i < 6 ; i++)
			{
				printf("The Stored Reference Voltage %lf\n", refs[i]);
			}

			printf( "Complete!\n" );
		}
		getchar();
	} while (1);
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

	printf( "\nMeasureReferences completed.\n" );

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
