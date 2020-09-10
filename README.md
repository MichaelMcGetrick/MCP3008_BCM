## SPI Communication with MCP3008 ADC using BCM2835 Library

* [Description](#description)
* [BCM2385 Library Installation](#installation)
* [Graphics](#graphics)

### Description
This repository provides the code for a Raspberry Pi application
to process an external signal at a required sampling rate. The
project implements the SPI protocol to communicate with a MCP3008
8-channel Analog to Digital Converter. The MCP3008 takes an analog
signal from a signal source (e.g. signal generator) and converts it
to a 10-bit digital representation.

The code will process the external signal by using the Broadcom 
BCM2835 library in order to interface with the SPI h/w
functionality of the Raspberry Pi Broadcom SoC.

### BCM2835 Library Installation

From the home directory (or other directory of your choice) get the latest version
of the library with: 

wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.xx.tar.gz

where 1.xx is the latest version.

Unzip the downloaded files with:
tar zxvf bcm2835-1.xx.tar.gz 

Go into unzipped folder with:
cd bcm2835-1.xx

Run the configure executable:
./configure

Execute makefile:
make

Then:
sudo make check

Then sudo make install



       	    	    
		
### Graphics		   
The signal can then be displayed by using appropriate graphics
code. The project will use the graphic_lx library to be found at:
https://github.com/UtterSense/Simple-Graphics/
     
       
       
       
       
             		
      
      
              
