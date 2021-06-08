CFLAGS = -Wall
CC = gcc
GPH_INCLUDE = /home/pi/CProjects/Graphics/Simple-Graphics/
GPH_SRC_DIR = ../../Graphics/Simple-Graphics/
DS_SRC_DIR = /home/pi/GitRepos/UtterSense/ds3231/
DS_INCLUDE = $(DS_SRC_DIR)

#Define source file for shared library:
SHR_LIB_SRC = ds3231
LIB_PATH=.
TARGET = bcm_spi
LINK_APP = main.c

#This is originakl versionand works!
all:
#	$(CC) $(CFLAGS) $(GPH_INCLUDE) main.c  graph.c mcp3008.c  ../../Graphics/Simple-Graphics/graphic_lx.c -lbcm2835 -lgraph -lm -o bcm_spi
	$(CC) $(CFLAGS) -I$(GPH_INCLUDE) -I$(DS_INCLUDE) main.c  graph.c mcp3008.c  ../../Graphics/Simple-Graphics/graphic_lx.c $(DS_SRC_DIR)ds3231.c -lbcm2835 -lgraph -lm -o bcm_spi

#	
	
#all: $(TARGET) 
#	Compile source code to a position independent object file
#$(TARGET):  $(DS_SRC_DIR)$(SHR_LIB_SRC).c  $(LINK_APP)
#	$(CC) $(CFLAGS) -I$(DS_INCLUDE) -c $(DS_SRC_DIR)$(SHR_LIB_SRC).c 
#	Compile shared library from position independent object file
#	$(CC) -shared  -o lib$(SHR_LIB_SRC).so $(SHR_LIB_SRC).o
#Create the main object file
#	$(CC) $(CFLAGS) -I$(GPH_INCLUDE) -I$(DS_INCLUDE) -c main.c  graph.c mcp3008.c  ../../Graphics/Simple-Graphics/graphic_lx.c -lbcm2835 -lgraph -lm 
#   Link library to the required user application	
#	$(CC) -I$(GPH_INCLUDE) -I$(DS_INCLUDE) -L$(PWD) -Wl,-rpath=$(LIB_PATH) -Wall -o $(TARGET) main.c graph.c mcp3008.c  ../../Graphics/Simple-Graphics/graphic_lx.c -lbcm2835 -lgraph -lm lib$(SHR_LIB_SRC).so  
#
	
	
	
	
	
clean:
	rm -rf *o bcm_spi
		
			
