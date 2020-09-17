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
#define SPI_BIT_ORDER     BCM2835_SPI_BIT_ORDER_MSBFIRST      //Bit order for MCP3008
#define SPI_DATA_MODE     BCM2835_SPI_MODE0                   //Default data mode
#define SPI_CS            BCM2835_SPI_CS0                     //Chip select
#define SPI_CLK_DIV       BCM2835_SPI_CLOCK_DIVIDER_4096     //Gives clock frequency of 0.68MHz (4096 -> 0.34MHz)


#define RD_MODE 	        1   //Single:1; Differential: 0
#define INPUT_CHAN        0 //7   //Analog input channel index
#define ARRAY_LEN	        3	//Array length for incoming data
#define SPI_CTRL_CFG      (RD_MODE << 7) | (INPUT_CHAN << 4)  //Configure byte for start bit and address data
#define VREF              3.3    //Reference voltage for analog measurements    
#define MAX_ANALOG_VAL    1024   //Max. integer value of 10 bit analog signal 

#define BUFFER_LEN        3  //Buffer length for SPI transmit and receive bytes

//ATTRIBUTES:
unsigned int bcm2835_ver;
char tx_buf[BUFFER_LEN], rx_buf[BUFFER_LEN];
      
                 

//FUNCTION PROTOTYPES ---------------------------------------------------------
        
int MCP3008_Init();
void MCP3008_Close();
float readSample();
uint16_t getVal(uint8_t msb,uint8_t lsb);
void transfer_byte(uint8_t val);
void loopback_test(uint8_t val);
unsigned int getBCM2835Version(void);

       
       
//---------------------------------------------------------------------------
#endif
