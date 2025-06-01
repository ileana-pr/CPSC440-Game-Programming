class game
{
private:
    int number_of_pairs;
    int number_of_moves;
    int pairs_found;
    int pairs_remaining;
    int game_board[5][5];

public:
    game();
    ~game();
    void setup();
};
