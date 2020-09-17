/*
 ======================================================================================
 Name        : main.c
 Author      : Michael McGetrick
 Version     :
 Copyright   : Your copyright notice
 Description : Program application to sample at a given frequency an incoming signal
              from theMCP3008 ADC, and display the signal graphically.
               
              NB: This program must be run as root to access GPIO and SPI functionality 
                  (Use sudo ./bcm_spi) 
 	 	 	   
 =====================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include "mcp3008.h"


//DEFINES ---------------------------------------
#define SAMPLING_RATE     0.5f  //Set to 1 if sampling at 1Hz or less
	

//ATTRIBUTES: -----------------------------------------
int EXIT_PROGRAM = 0;
unsigned int sample_delay;


//GRAPH PLOTTING: -------------------------------------

//----------------------------------------------------



//FUNCTION DECLARATIONS -------------------------
void ctrl_c_handler(int sig);


//-----------------------------------------------
int main(void) {

       //Register handler for capturing CTL-C signal:
	signal(SIGINT,ctrl_c_handler);
            

       //Initialise SPI for MCP3008:
       printf("Initialising SPI for MCP3008 peripheral.....\n");
       printf("BCM2835 Library version:   %d\n\n",getBCM2835Version());
       MCP3008_Init(SAMPLING_RATE);
         
                   
       sample_delay = getSamplingRate();
       printf("Delay in millisecs: %d\n",sample_delay);
              
       uint cnt = 0;
       while(EXIT_PROGRAM == 0)
       {             
           float volts = readSample();
           printf("Count: %d\n", cnt);
           printf("Voltage reading: %.2f\n",volts);
           bcm2835_delay(sample_delay);   
           cnt += 1;              
       }                    
       
       printf("Closing down SPI interface...\n");
       MCP3008_Close();
       
       printf("SPI closed down - exiting program\n");
                     
       return 0;

}//main


//NB: This handler is working for the CTL-C keyboard signal
//	  This will exit the while loop so as to exit the program gracefully
//	  (We need to close the connection to the serial terminal)
void ctrl_c_handler(int sig)
{
   
   if(sig == SIGINT) //Check it is the right user ID //NB: Not working at the moment
   {
         printf("\nWe have received the CTRL-C signal - aborting sample looping!\n");
         EXIT_PROGRAM = 1; //This will stop program
         
   }
   
         
}//ctrl_c_handler(int sig)

