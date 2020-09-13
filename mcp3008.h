//---------------------------------------------------------------------------
#ifndef MCP3008_H
#define MCP3008_H


#include <stdbool.h>
#include <bcm2835.h>  //Broadcom library  

/*-----------------------------------------------------------------------------
   AUTHOR:            M.J. McGetrick
                      (c) Copyright 2020 M.J. McGetrick
   DATE:
   DESCRIPTION:       MPC3008
                      Suite of functions to interface with the MCP3008
                      ADC via the SPI protocol.
                      
------------------------------------------------------------------------------*/

//DEFINES
#define SPI_BIT_ORDER   BCM2835_SPI_BIT_ORDER_MSBFIRST      //Bit order for MCP3008
#define SPI_DATA_MODE   BCM2835_SPI_MODE0                   //Default data mode
#define SPI_CS          BCM2835_SPI_CS0                     //Chip select
#define SPI_CLK_DIV     BCM2835_SPI_CLOCK_DIVIDER_2048     //Gives clock frequency of 0.68MHz


//ATTRIBUTES:
unsigned int bcm2835_ver;
      
                 

//FUNCTION PROTOTYPES ---------------------------------------------------------
        
int MCP3008_Init();
void MCP3008_Close();
void transfer_byte(uint8_t val);
void loopback_test(uint8_t val);
unsigned int getBCM2835Version(void);

       
       
//---------------------------------------------------------------------------
#endif
