/*-----------------------------------------------------------------------------
   AUTHOR:            M.J. McGetrick
                      (c) Copyright 2020 M.J. McGetrick
   DATE:
   DESCRIPTION:       MPC3008
                      Suite of functions to interface with the MCP3008
                      ADC via the SPI protocol.
                      
------------------------------------------------------------------------------*/
#include "mcp3008.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

//---------------------------------------------------------------------------
int MCP3008_Init()
{
   
   if (!bcm2835_init())
   {
      printf("bcm2835_init failed. Please check that you are running as root.\n");
      return 1;
   }   

   if (!bcm2835_spi_begin())   //Configure the designated GPIO pins for SPI use
   {
      printf("bcm2835_spi_begin failed. Please check that you are running as root.\n");
      return 1;
   }

   bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      
   bcm2835_spi_setDataMode(SPI_DATA_MODE);                   
   bcm2835_spi_setClockDivider(SPI_CLK_DIV); 
   bcm2835_spi_chipSelect(SPI_CS);                      
   bcm2835_spi_setChipSelectPolarity(SPI_CS, LOW);  //Select chip on LOW    
   
   return 0;
   
      
}//MCP3008_Init


void MCP3008_Close()
{
   //Revert SPI pins back to default GPIO behaviour
   bcm2835_spi_end();
   
   //Close the bcm library and deallocate memory
   bcm2835_close();
   
      
   
}//MCP3008_Close()


unsigned int getBCM2835Version(void)
{
   bcm2835_ver = bcm2835_version();
      
   return bcm2835_ver;
   
}//getBCM2835Version   

