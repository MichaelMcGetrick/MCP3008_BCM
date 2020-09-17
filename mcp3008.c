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
int MCP3008_Init(float sample_rate)
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

   //Configure the SPI:
   bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      
   bcm2835_spi_setDataMode(SPI_DATA_MODE);                   
   bcm2835_spi_setClockDivider(SPI_CLK_DIV); 
   bcm2835_spi_chipSelect(SPI_CS);                      
   bcm2835_spi_setChipSelectPolarity(SPI_CS, LOW);  //Select chip on LOW    
   
     
   //Define MOSI transmit data  
   tx_buf[0] = 0x01;                      //Least significant bit the start bit 
   tx_buf[1] = SPI_CTRL_CFG;              //Define inupt mode and input pin address
   tx_buf[2] = 0x01;                      //Don't care bits
         
   //Set required delay for sampling rate:
   delay_ms = (1.0/(float)sample_rate)*1000;
                      
   return 0;
   
      
}//MCP3008_Init


float readSample()
{      
   
   float volts;
   
   uint16_t val;
   
   bcm2835_spi_transfernb(tx_buf,rx_buf,BUFFER_LEN);
   
   rx_buf[1] &= 0x03;    //Define most significant byte
   val = getVal(rx_buf[1],rx_buf[2]);
   
   //Convert to floating point:
   volts = ((float)val*VREF)/MAX_ANALOG_VAL;

   return volts;
   
}//ReadSample   


uint16_t getVal(uint8_t msb,uint8_t lsb)
{
   
   uint16_t val_msb = msb;
   uint16_t val_lsb = lsb;
	val_msb = val_msb << 8;
   
   return  val_msb | val_lsb;
   
}//getVal



void transfer_byte(uint8_t val)
{
   // Send a byte to the slave and simultaneously read a byte back from the slave
   // If you tie MISO to MOSI, you should read back what was sent
   uint8_t send_data = val;
   uint8_t read_data = bcm2835_spi_transfer(send_data);
   printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
   if (send_data != read_data)
   {
     printf("Input and output bytes do not match - do you have aloopback configuration from mOSI to  MISO?\n");
   }
   else
   {
      printf("Loopback test successful!\n");
   }
   
}//transfer_byte   

   

void MCP3008_Close()
{
   //Revert SPI pins back to default GPIO behaviour
   bcm2835_spi_end();
   
   //Close the bcm library and deallocate memory
   bcm2835_close();
   
   
}//MCP3008_Close()


unsigned int getSamplingRate(void)
{
   return delay_ms;
   
}//getSamplingRate   


unsigned int getBCM2835Version(void)
{
   bcm2835_ver = bcm2835_version();
      
   return bcm2835_ver;
   
}//getBCM2835Version   


//Loopback test to check RPI SPI functionality
void loopback_test(uint8_t val)
{
   MCP3008_Init(2.0);   //Define dummy paramter - not used for sampling
       
   //Transfer one byte for loopback test:
   transfer_byte(val);           
       
   MCP3008_Close();
      
}//loopback_test



