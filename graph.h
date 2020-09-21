#ifndef GRAPH_H
#define GRAPH_H

/*
 ============================================================================
 Name        : graph.c
 Author      : Michael McGetrick
 Version     :
 Copyright   : 
 Description : Graph module to set up graph and animamation plotting 
 	 	 	      for signal from MCP3008
 	 	 	         

 	 	 	    #endif
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdint.h>
#include <signal.h>

#include <fcntl.h> 		//File Control Definitions
#include <time.h>

#include "graphic_lx.h"


//USER DEFINES: ------------------------------------------------------------

//Data buffer for plot
#define DATA_LEN  		200  //This is also length of x axis on plot
#define REFRESH_MODE	0	//Plot refresh mode:   0: Per new sample; 1: Data buffer complete
#define SAMPLE_RATE     1000 //50  //(samples per second): Known rate from MCU (could use a header from MCU to dynamically define this)
#define REFRESH_CNT     0.5*SAMPLE_RATE   //Count at which to refresh graph
#define GRAPH_MODE		1   //0: Simulation data; 1: Real data from Serial Port      
#define DATA_SKIP		0//500  //Define the number of incoming data samples to ignore before string plotting 
							//Avoids any sprious data coming through on initial startup/reset
							
#define DC_OFFSET		-2.25//-2.5//Define offset to match dc offset provided in MCU							
									//There appears to be 0.25 difference in expected value (could be down to resistor error toloerance)


//GRAPH PLOTTING:
#define X_WIN_SIZE   640      //NB: These appear to be fixed for Linux implementation
#define Y_WIN_SIZE   475   

#define GRAPH_TITLE  "EEG SIMULATION SIGNAL"
#define X_LABEL      "Time"
#define Y_LABEL      "VOLTS"
#define BCK_COLOR     0             //Color of graph background
#define TRACE_COLOR   2             //Color of plot tracw

#define LEGEND_CAPTION1	"Vmax:            V"
#define LEGEND_CAPTION2	"Vmin:             V"
#define LEGEND_CAPTION3	"Vavg:             V"
#define LEGEND_CAPTION4	"Vpp:              V"

#define PLOT_MODE    0
#define LOG_MODE     0

//NB - Ensure we do not define 0 for log plots
#define Y_MIN        -3.0
#define Y_MAX        3.0
#define X_MIN        0.0
#define X_MAX        DATA_LEN

#define X_INT        10
#define Y_INT        10
#define G_INT        10

#define SHOW_GRID    true  //Show gradations 
#define X_GRAD       true
#define Y_GRAD       true
#define X_SHOW       true
#define Y_SHOW       true
#define ORI_LINE     true    //Draw the x axis origin line
#define BITMAP       false

//Audio files:
#define AUDIOFILE      "test.wav"
#define INI_AUDIOFILE   "ini.wav"
#define NUM_CHANS       1
//#define SAMPLE_RATE     11000
#define BITS_PER_SAMPLE 16
#define BITS_PER_SAMPLE 16

//Legend
extern bool legend_flg;  //Flag to include legend
							
//---------------------------------------------------------------------------------------------------------------------

char buf[255];
float PLOT_BUFFER[DATA_LEN], PLOT_COPY[DATA_LEN];
extern int refCnt;

extern double vmax;
extern double vmin;
extern double vavg;
extern double vpp ;
extern double vmaxCopy,vminCopy,vavgCopy,vppCopy;


//PLOTTING ATTRIBUTES
//Simulator incrementor
extern int j;
//Plotting control flag
extern bool m_bPlot;
extern bool mSuppress;
extern float dataX[DATA_LEN],dataY[DATA_LEN];
extern bool plotStart;


//FUNCTION DECLARATIONS -------------------------
void plotTrace(int color);
void refreshCanvas();
void removeGrid();
void copyDataBuf();
void copyLegendData();


//-----------------------------------------------------------------------
#endif
