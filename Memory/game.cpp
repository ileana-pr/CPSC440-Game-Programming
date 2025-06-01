#include "game.h"

void game::setup()
{
    //initialize the game
    number_of_moves = 0;
    pairs_found = 0;
    pairs_remaining = 0;

    //initialize the game board
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            game_board[i][j] = 0;
        }
    }
}
//get_mouse_input: use an if else statement to figure out wat box is being selected  
void get_mouse_input(int &x, int &y);

// draw_objects: given an x and y location, it will draw the appropriate object x and y are the center of the box that was selected; you can draw any object. will call get_shape to figure out which shape is supposed to be drawn. 
void draw_objects(int x, int y);

// get_shape: given an x and y location, it will return the shape that is supposed to be drawn. 
int get_shape(int x, int y);

// set_shape: given an x and y location, it will set the shape that is supposed to be drawn. 
int set_shape(int x, int y);

// compare_shapes: given an x and y location, it will compare the shape that is supposed to be drawn. 
int compare_shapes(int x, int y);

// reset_game: given an x and y location, it will reset the game. 
void reset_game();

// clear_game: given an x and y location, it will clear the game. 
void clear_game();

// done: game is done when there are no pairs remaining to find. 
void done();    





