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
    bool game_over(int pairs_remaining);
    void reset_game();
    bool is_card_revealed(int row, int col);   // checks if card is flipped
    bool is_card_matched(int row, int col);    // checks if card is matched
    int get_shape(int row, int col);      // gets the shape at position
    bool is_first_card_flipped();              // checks if first card is flipped
    bool flip_first_card(int row, int col);    // flips first card
    bool flip_second_card(int row, int col);   // flips second card and checks match
    int get_pairs_remaining();                 // gets number of pairs remaining
    int get_number_of_moves();                 // gets number of moves made
    int get_pairs_found();                     // gets number of pairs found
    void hide_mismatched_cards();              // hides cards after mismatch
    bool compare_shapes(int row1, int col1, int row2, int col2);  // compares two cards
    void update_game(double delta_time);       // updates game timing
};
