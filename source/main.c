// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: NightFox & Co., 2009-2011
//
// NightFox's Lib Template
// http://www.nightfoxandco.com

#include <stdio.h>
#include <nds.h>
#include <gl2d.h>

// Definitions that might be needed for later
#define HALF_WIDTH (SCREEN_WIDTH / 2)
#define HALF_HEIGHT (SCREEN_HEIGHT / 2)

// Struct definitions
struct snakeHead
{
	int x;
	int y;
	int width;
	int height;
	int color;
};

// Function declarations
void draw(struct snakeHead head);

int main(int argc, char **argv)
{
    videoSetMode(MODE_5_3D); // Setting video mode
    consoleDemoInit(); // Initialize console
    glScreen2D(); // Initialize GL in 2d mode
 

    printf("\n Hello World!");
    
    // Creating the snake head
    struct snakeHead head;
    head.x = HALF_WIDTH;
    head.y = HALF_HEIGHT;
    head.width = 5;
    head.height = 5;
    head.color = RGB15(255, 255, 255);

    int keys;

    while (1)
    {
	// Reading input
	scanKeys();

	keys = keysDown();

	if (keys & KEY_UP)
	{
		head.y -= 5;
	}
	else if (keys & KEY_DOWN)
	{
		head.y += 5;
	}

	if (keys & KEY_LEFT)
	{
		head.x -= 5;
	}
	else if (keys & KEY_RIGHT)
	{
		head.x += 5;
	}
	
	// Updating and drawing the screen
	draw(head);
	glFlush(0);
	    
        // Wait for the screen refresh
        swiWaitForVBlank();
    }

    // If this is reached, the program will return to the loader if the loader
    // supports it.
    return 0;
}

void draw(struct snakeHead head)
{
	glBegin2D(); // Set up GL for 2d mode
		
	//glBoxFilled(200, 10, 250, 180, RGB15(255, 255, 255));
	glBoxFilled(head.x - head.width, head.y - head.height, head.x + head.width, head.y + head.height, head.color);

	glEnd2D();
}

