/*
A simple example of using the gfx library.
CSE 20211
9/7/2011
by Prof. Thain
*/

#include <stdio.h>
#include "gfx.h"

int main()
{
	int ysize = 600;
	int xsize = 800;

	char c;

	// Open a new window for drawing.
	gfx_open(xsize,ysize,"Example Graphics Program");

	gfx_clear_color(255,255,255);
	gfx_clear();
/*
	// Set the current drawing color to green.
	gfx_color(255,0,0);
	// Draw a triangle on the screen.
	gfx_line(50,50,100,500);
//	gfx_line(200,100,150,150);
//	gfx_line(150,150,100,100);

	gfx_color(0, 255,0);
	// Draw a triangle on the screen.
	gfx_line(100,50,150,500);
	gfx_color(0,0,255);
	// Draw a triangle on the screen.
	gfx_line(150,50,200,500);
	gfx_color(255,255,0);
	// Draw a triangle on the screen.
	gfx_line(200,50,250,500);
	gfx_color(255,255,255);
	// Draw a triangle on the screen.
	gfx_line(250,50,300,500);
	gfx_color(100,100,100);
	// Draw a triangle on the screen.
	gfx_line(300,50,350,500);
	gfx_color(0,0,0);
	// Draw a triangle on the screen.
	gfx_line(350,50,400,500);
*/

	gfx_color(255,0,0);
	gfx_fillcircle(50,50,100);
	//gfx_fillrectangle(50,50,100,100);	
	gfx_color(0,255,0);
	gfx_fillcircle(200,100,200);

	//gfx_fillrectangle(200,100,150,50);	
	gfx_color(0,0,255);
	gfx_fillcircle(400,200,350);

	//gfx_fillrectangle(400,200,200,20);



	while(1) {
		// Wait for the user to press a character.
		c = gfx_wait();
/*		if (c==0x01)
		{
			printf("1 - left button\n");
		}
		else if (c==0x02)
		{
			printf("2 - middle button\n");
		}
		else if (c==0x03)
		{
			printf("3 - right button\n");
		}
		else
			printf("%c \n",c);*/
		// Quit if it is the letter q.
		//printf("MOuse position x pos is %d and y pos is %d \n", gfx_xpos(),gfx_ypos());
		if(c=='q') break;
	}

	return 0;
}
