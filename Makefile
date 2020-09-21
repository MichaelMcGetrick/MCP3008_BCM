CFLAGS = -Wall
CC = gcc
INCLUDES = -I/home/pi/CProjects/Graphics/Simple-Graphics

all:
	$(CC) $(CFLAGS) $(INCLUDES) main.c  graph.c mcp3008.c  ../../Graphics/Simple-Graphics/graphic_lx.c -lbcm2835 -lgraph -lm -o bcm_spi

clean:
	rm -rf *o bcm_spi
		
			
