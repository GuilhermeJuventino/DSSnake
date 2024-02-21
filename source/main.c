#include <stdio.h>
#include <string.h>
#include <nds.h>
#include <gl2d.h>

// Definitions that might be needed for later
#define HALF_WIDTH (SCREEN_WIDTH / 2)
#define HALF_HEIGHT (SCREEN_HEIGHT / 2)
#define MAX_SEGMENTS (1000)
#define MAX_FPS (60)

// Struct definitions
struct snakeHead
{
	int x;
	int y;
	int width;
	int height;
	int color;
	int size;
	int delay;
	char* direction;
};

struct segment
{
	int x;
	int y;
};

struct segment segments[MAX_SEGMENTS];

// Type definitions
typedef enum gameState
{
	TITLE_SCREEN,
	IN_GAME,
	GAME_OVER
} gameState;

// Function declarations
void drawSnake(struct snakeHead head, struct segment segments[]);
void moveSnake(struct snakeHead *head, struct segment segments[]);
void changeGameState(gameState *state, int stateNum);

// Timer
int timer = 0;

int main(int argc, char **argv)
{
    videoSetMode(MODE_5_3D); // Setting video mode
    consoleDemoInit(); // Initialize console
    glScreen2D(); // Initialize GL in 2d mode
    
    // Initial game state
    gameState state = TITLE_SCREEN;
    gameState *stateReference = &state;

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

    head.delay = 5;

    segments[0].x = head.x;
    segments[0].y = head.y - 10;

    segments[1].x = head.x;
    segments[1].y = head.y - 20;

    segments[2].x = head.x;
    segments[2].y = head.y - 30;

    struct snakeHead *headReference = &head; 

    int keys;

    while (1)
    {	
	// Reading input
	scanKeys();

	switch (state)
	{
		case TITLE_SCREEN:
			printf("\nTitle Screen");
			
			keys = keysUp();

			if (keys & KEY_START)
			{
				changeGameState(stateReference, 1);
			}
			break;
		case IN_GAME:
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
	
			// Updating and drawing the screen
	
			// Waiting for the delay timer to end before moving the snake
			if (timer >= head.delay)
			{
				moveSnake(headReference, segments);

				// Reseting the timer
				timer = 0;
			} else
			{
				// Updating the timer
				timer++;
			}
			drawSnake(head, segments);
			
			break;
		case GAME_OVER:
			printf("\nGame Over");

			keys = keysUp();

			if (keys)
			{
				changeGameState(stateReference, 0);
			}
			break;
	}
	
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
		
	// Drawing the snake's head
	glBoxFilled(head.x - head.width, head.y - head.height, head.x + head.width, head.y + head.height, head.color);

	// Drawing the snake's body
	for (int i = 0; i < head.size; i++)
	{
		glBoxFilled(segments[i].x - head.width, segments[i].y - head.height, segments[i].x + head.width, segments[i].y + head.height, head.color);
	}

	glEnd2D();
}

void moveSnake(struct snakeHead *head, struct segment segments[])
{
	int prev_x = head -> x;
	int prev_y = head -> y;
	
	// Moving the head	
	if (strcmp(head -> direction, "UP") == 0)
	{
		head -> y -= 5;
	} else if (strcmp(head -> direction, "DOWN") == 0)
	{
		head -> y += 5;
	} else if (strcmp(head -> direction, "LEFT") ==  0)
	{
		head -> x -= 5;
	} else if (strcmp(head -> direction, "RIGHT") == 0)
	{
		head -> x += 5;

	}
	
	// Moving the segments
	for (int i = 0; i < head -> size; i++)
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

void changeGameState(gameState *state, int stateNum)
{
	*state = stateNum;
}
