// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: NightFox & Co., 2009-2011
//
// NightFox's Lib Template
// http://www.nightfoxandco.com

#include <stdio.h>
#include <string.h>
#include <nds.h>
#include <gl2d.h>

// Definitions that might be needed for later
#define HALF_WIDTH (SCREEN_WIDTH / 2)
#define HALF_HEIGHT (SCREEN_HEIGHT / 2)
#define MAX_SEGMENTS (1000)

// Struct definitions
struct snakeHead
{
	int x;
	int y;
	int width;
	int height;
	int color;
	int size;
	char* direction;
};

struct segment
{
	int x;
	int y;
};

// Function declarations
void drawSnake(struct snakeHead head, struct segment segments[]);
void moveSnake(struct snakeHead head, struct segment segments[]);

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
    head.direction = "DOWN";

    int starting_size = 3;
    head.size = starting_size;

    struct segment segments[MAX_SEGMENTS];
    segments[0].x = head.x;
    segments[0].y = head.y - 10;

    segments[1].x = head.x;
    segments[1].y = head.y - 20;

    int keys;

    while (1)
    {
	// Reading input
	scanKeys();

	keys = keysHeld();
	
	if (keys & KEY_UP && strcmp(head.direction, "DOWN") != 0)
	{
			head.direction = "UP";
	} else if (keys & KEY_DOWN && strcmp(head.direction, "UP") != 0)
	{
		head.direction = "DOWN";
	}

	if (keys & KEY_LEFT && strcmp(head.direction, "RIGHT") != 0)
	{
		head.direction = "LEFT";
	} else if (keys & KEY_RIGHT && strcmp(head.direction, "LEFT") != 0)
	{
		head.direction = "RIGHT";
	}
	
	/*
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
	*/
    	printf("\n %s", head.direction);
	
	// Updating and drawing the screen
	moveSnake(head, segments);
	drawSnake(head, segments);
	glFlush(0);
	    
        // Wait for the screen refresh
        swiWaitForVBlank();
    }

    // If this is reached, the program will return to the loader if the loader
    // supports it.
    return 0;
}

void drawSnake(struct snakeHead head, struct segment segments[])
{
	glBegin2D(); // Set up GL for 2d mode
		
	//glBoxFilled(200, 10, 250, 180, RGB15(255, 255, 255));
	// Drawing the snake's head
	glBoxFilled(head.x - head.width, head.y - head.height, head.x + head.width, head.y + head.height, head.color);

	// Drawing the snake's body
	for (int i = 0; i < head.size - 1; i++)
	{
		glBoxFilled(segments[i].x - head.width, segments[i].y - head.height, segments[i].x + head.width, segments[i].y + head.height, head.color);
	}

	glEnd2D();
}

void moveSnake(struct snakeHead head, struct segment segments[])
{
	int prev_x = head.x;
	int prev_y = head.y;

	if (strcmp(head.direction, "UP") == 0)
	{
		head.y -= 5;

		for (int i = 0; i < head.size - 1; i++)
		{
			int new_x = prev_x;
			int new_y = prev_y;

			int seg_prev_x = segments[i].x;
			int seg_prev_y = segments[i].y;

			segments[i].x = new_x;
			segments[i].y = new_y;

			prev_x = seg_prev_x;
			prev_y = seg_prev_y;

		}
	} else if (strcmp(head.direction, "DOWN") == 0)
	{
		head.y += 5;

		for (int i = 0; i < head.size - 1; i++)
		{
			int new_x = prev_x;
			int new_y = prev_y;

			int seg_prev_x = segments[i].x;
			int seg_prev_y = segments[i].y;

			segments[i].x = new_x;
			segments[i].y = new_y;

			prev_x = seg_prev_x;
			prev_y = seg_prev_y;
		}
	} else if (strcmp(head.direction, "LEFT") ==  0)
	{
		head.x -= 5;

		for (int i = 0; i < head.size - 1; i++)
		{
			int new_x = prev_x;
			int new_y = prev_y;

			int seg_prev_x = segments[i].x;
			int seg_prev_y = segments[i].y;

			segments[i].x = new_x;
			segments[i].y = new_y;

			prev_x = seg_prev_x;
			prev_y = seg_prev_y;
		}
	} else if (strcmp(head.direction, "RIGHT") == 0)
	{
		head.x += 5;

		for (int i = 0; i < head.size - 1; i++)
		{
			int new_x = prev_x;
			int new_y = prev_y;

			int seg_prev_x = segments[i].x;
			int seg_prev_y = segments[i].y;

			segments[i].x = new_x;
			segments[i].y = new_y;

			prev_x = seg_prev_x;
			prev_y = seg_prev_y;
		}
	}
}
