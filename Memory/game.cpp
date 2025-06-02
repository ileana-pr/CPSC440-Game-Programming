#include "game.h"
#include <cstdlib>
#include <ctime>

game::game()
{
    // constructor
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            game_board[i][j] = 0;
            revealed[i][j] = false;
            matched[i][j] = false;
        }
    }
    first_card_flipped = false;
    showing_mismatch = false;
}

game::~game()
{
    // destructor 
}

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
    srand((unsigned int)time(nullptr));
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

// compare two cards to see if they match
bool game::compare_shapes(int row1, int col1, int row2, int col2) {
    // check if positions are valid
    if (row1 < 0 || row1 >= 5 || col1 < 0 || col1 >= 5 ||
        row2 < 0 || row2 >= 5 || col2 < 0 || col2 >= 5) {
        return false;
    }
    
    // compare the shape values
    return game_board[row1][col1] == game_board[row2][col2];
}


// reset_game: given an x and y location, it will reset the game. 
void game::reset_game() {
    // reset game state
    number_of_moves = 0;
    pairs_found = 0;
    pairs_remaining = 12;
    // reinitialize the game board
    setup();
}

// random_create: given the number of cards, it will create the   
bool game::done()
{
    if (pairs_remaining == 0)
    {
        return true;
    }
    return false;
}

// placeholder for handle_card_click - testing grid display
void game::handle_card_click(int row, int col)
{
   
}




