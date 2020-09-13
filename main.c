/*
 ======================================================================================
 Name        : main.c
 Author      : Michael McGetrick
 Version     :
 Copyright   : Your copyright notice
 Description : Program application to sample at a given frequency an incoming signal
              from theMCP3008 ADC, and display the signal graphically.
               
              NB: This program must be run as root to access GPIO and SPI functionality 
 	 	 	   
 =====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "mcp3008.h"


//DEFINES ---------------------------------------



//GRAPH PLOTTING: -----------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------


//FUNCTION DECLARATIONS -------------------------
//TBD
//-----------------------------------------------
int main(void) {

       //Initialise SPI for MCP3008:
       printf("Initialising SPI for MCP3008 peripheral.....\n");
       printf("BCM2835 Library version:   %d\n\n",getBCM2835Version());
       //MCP3008_Init();
       //MCP3008_Close();
       
       //Do loopback test:
       loopback_test(0xae);
                     
       return 0;

}//main
