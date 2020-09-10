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
      return 0;
   }   

      
}//MCP3008_Init

