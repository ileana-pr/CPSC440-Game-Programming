#include "game.h"
#include <cstdlib>
#include <ctime>

void game::setup()
{
    //initialize game
    number_of_moves = 0;
    pairs_found = 0;
    // 12 pairs to find
    pairs_remaining = 12; 

    // create array with 12 pairs + 1 empty space
    int cards[25];
    int index = 0;
    
    // add 12 pairs 
    for (int shape = 1; shape <= 12; shape++) {
        cards[index++] = shape;
        cards[index++] = shape;
    }
    // add 1 empty space
    cards[24] = 0;
    
    // shuffle the cards
    srand(time(nullptr));
    for (int i = 24; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    
    // place shuffled cards in grid
    index = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            game_board[i][j] = cards[index++];
        }
    }
}



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

// random_create: given the number of cards, it will create the   
bool game::done()
{
    if (pairs_remaining == 0)
    {
        return true;
    }
    return false;
}




