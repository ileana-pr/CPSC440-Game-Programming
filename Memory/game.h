class game
{
private:
    int number_of_pairs;
    int number_of_moves;
    int pairs_found;
    int pairs_remaining;
    int game_board[5][5];
    bool revealed[5][5];        // tracks currently flipped cards
    bool matched[5][5];         // tracks matched pairs
    int first_card_row, first_card_col;   // first flipped card position
    int second_card_row, second_card_col; // second flipped card position
    bool first_card_flipped;    // true if waiting for second card
    bool showing_mismatch;      // true during 5 second mismatch display
 
public:
    game();
    ~game();
    void setup();
    bool done();
    void reset_game();
    void handle_card_click(int row, int col);  // handles when card is clicked 
    bool is_card_revealed(int row, int col);   // checks if card is flipped
    bool is_card_matched(int row, int col);    // checks if card is matched
    void hide_mismatched_cards();              // hides cards after mismatch
    bool compare_shapes(int row1, int col1, int row2, int col2);  // compares two cards
};
