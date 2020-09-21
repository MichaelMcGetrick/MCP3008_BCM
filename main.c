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
                   
             RPI connections(SPI0):
             Phys Pin	GPIO	Function
             19			10		MOSI
             21			9		MISO
             23			11		CLK
             24         8		CE   
                   
 	 	 	   
 =====================================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>

#include "graph.h"
#include "mcp3008.h"



//DEFINES ---------------------------------------
#define SAMPLING_RATE     1000.0f  
	

//ATTRIBUTES: -----------------------------------------
int EXIT_PROGRAM = 	0;
char *PROG_MODE  = 	"TEST";		//TEST: GRAPHICS
uint64_t sample_delay;
float data[1000];

//File attributes
FILE *fp;
char *filename = "data.csv";
bool saveToFile = true;



//FUNCTION DECLARATIONS -------------------------
void ctrl_c_handler(int sig);
void doTest();
void doGraphics();

//-----------------------------------------------
int main(void) {

   //Register handler for capturing CTL-C signal:
	signal(SIGINT,ctrl_c_handler);
            
	              
       
	//Initialise SPI for MCP3008:
	printf("Initialising SPI for MCP3008 peripheral.....\n");
	printf("BCM2835 Library version:   %d\n\n",getBCM2835Version());
	MCP3008_Init(SAMPLING_RATE);
		
					 
	sample_delay = getSamplingRate();
	printf("Delay in micro-secs: %lld\n",sample_delay);
			  
	 
	 
	if(strcmp(PROG_MODE,"TEST") == 0)
	{
		doTest();
		
	}
	else if(strcmp(PROG_MODE,"GRAPHICS") == 0)
	{
		 doGraphics();
	}	 
		 

}//main


void doGraphics()
{
	//Initialise Graphics
	Graphic_Init(X_WIN_SIZE,Y_WIN_SIZE,PLOT_MODE,LOG_MODE, X_LABEL, Y_LABEL, GRAPH_TITLE,
				Y_MIN,Y_MAX,X_MIN, X_MAX,
				X_INT,Y_INT,X_GRAD,Y_GRAD,
				SHOW_GRID, G_INT,
				X_SHOW,Y_SHOW,ORI_LINE,BITMAP,
				BCK_COLOR, AUDIOFILE, INI_AUDIOFILE,
				NUM_CHANS, SAMPLE_RATE, BITS_PER_SAMPLE);
		
	 
	//Setup Legend:
	if(legend_flg)
	{
		l_caps.vmax_caption = LEGEND_CAPTION1;
		l_caps.vmin_caption = LEGEND_CAPTION2;
		l_caps.vavg_caption = LEGEND_CAPTION3;
		l_caps.vpp_caption = LEGEND_CAPTION4;
		legendCaptions(l_caps);
	}	
					
	  
	  
	  
	
	int count = 0;
	float volts;
	while(EXIT_PROGRAM == 0)
	{
		
		volts = readSample();
				
		//Signal bounds check (to catch erroneous values)
		//Seems to be blis on Graphics side (if we lower refresh rate, they disappear)
		if(volts > Y_MAX)
		{
			volts = Y_MAX;
			mSuppress = true;
			
		 }	
		if(volts < Y_MIN)
		{
			volts = Y_MIN;
			mSuppress = true;
		 }
		
		if(count >= DATA_SKIP)   //Ignore first few data points
		{
			
			if (count == DATA_SKIP)
			{
				plotStart = true;	
			}
			
			
			//Shift data array elemnents to left and add current sample to end:
			for(int i=0;i < DATA_LEN-1;i++)
			{
				PLOT_BUFFER[i]=PLOT_BUFFER[i+1];
			}
		
			
			//PLOT_BUFFER[DATA_LEN-1] = (float) volts + DC_OFFSET;
			PLOT_BUFFER[DATA_LEN-1] = (float) volts;
									
			
			//Plot the signal	
			if(refCnt == REFRESH_CNT)
			{
				
				//end = clock();
				//sample_time = (double)(end-start)/CLOCKS_PER_SEC;
				
				//Refresh for next plot (put data points back tograph background color):
				if(plotStart == true)
				{
					//Do not Refreshcanvas before firsttrace has been done
					plotStart = false;
					//Capture copy of initial data buffer
					
				}
				else
				{
					refreshCanvas();
					//Refresh legend area:
					if(legend_flg)
					 {
						l_data.vmax = vmaxCopy;
						l_data.vmin = vminCopy;
						l_data.vavg = vavgCopy;
						l_data.vpp = vppCopy;
						legend(l_data,true); //This should erase previous data write
						//legend_flg = false; //temp
					 }
					
					
				 }		
				
				
				plotTrace(TRACE_COLOR);
				graduations(15);  //Refresh grduations
				
				copyDataBuf();  //Copy current graph trace
				copyLegendData();
											
				
				if(legend_flg)
				{
					 l_data.vmax = vmax; //sigFreq;
					 l_data.vmin = vmin; //vpp;
					 l_data.vavg = vavg; //Mean voltage
					 l_data.vpp = vpp;  //Peak to peak voltage
					legend(l_data,false); //Redraw legend
					//legend_flg = false; //temp
				}
					
				
				
				refCnt = 1;
			}	
			  else
			  {
				//Advance refresh counter:
				 refCnt = refCnt + 1;
			 }
			  
			  
			 
		}//count
		
		 count = count + 1;	
		 if(count == DATA_SKIP)
		 {
			//Remove grid for animation:
			//removeGrid();

		}					

	}//while
	
	
	printf("Closing down SPI interface...\n");
	MCP3008_Close();
	printf("SPI closed down\n");
	
	//Close graphics:
	delay(5000);
	closegraph();
	
	printf("Exiting program\n");              
	exit(0);
	
		
}//doGraphics


void doTest()
{
	
	 //Sample and save data to file for subsequent analysis:
	 
	 //Open file for data:
	 if( (fp=fopen(filename,"wt")) == NULL)
	 {
		printf("Error opening file -aboritng program!\n");
		exit(0);	 
	 }
	 
	 uint cnt = 0;
	 uint max_cnt = 1000;
	 //while(EXIT_PROGRAM == 0)
	 for(int i=0; i<1000;i++)
	 {             
		  data[i] = readSample();
		  //printf("Count: %d\n", cnt);
		  //printf("Voltage reading: %.2f\n",volts);
		  //fprintf(fp,"%d%c%.2f\n",cnt,',',volts);
		  //fprintf(fp,"%.2f\n",volts);
		  
		  bcm2835_delayMicroseconds(sample_delay);   
		  //cnt += 1;      
					 
	 } 
						  
		
	 //Save sampled data to file:
	 for(int i=0;i<1000;i++)
	 {
		 fprintf(fp,"%.2f\n",data[i]);
	 } 
	 	 
	 //Close file:
	 fclose(fp);
	 printf("Data file closed\n");
	 
	 printf("Closing down SPI interface...\n");
	 MCP3008_Close();
	 printf("SPI closed down\n");
	 
	 
	 printf("Exiting program\n");              
	 exit(0);					
	 
		
}//doTest	



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

