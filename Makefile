CFLAGS = -Wall
INCLUDES = -I/home/pi/CProjects/Graphics/Simple-Graphics

all:
	gcc $(CFLAGS) $(INCLUDES) main.c  mcp3008.c ../../Graphics/Simple-Graphics/graphic_lx.c -lbcm2835 -lgraph -lm -o bcm_spi

clean:
	rm -rf *o bcm_spi
		
			
