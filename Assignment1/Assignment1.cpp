#include <iostream>
#include<allegro5/allegro.h> 
#include "logic.cpp"

logic game; //instance of logic 
bool finished = false; 
bool timeOut = false; 
string result; 

void *input(ALLEGRO_THREAD *ptr, void *arg); 
void *timer(ALLEGRO_THREAD *ptr, void *arg); 

int main() {

    game.introduction(); 
    // Read file into game.readFile() 
    game.readFile("dictionary.txt"); 
    
    ALLEGRO_THREAD *create1 = NULL, *create2 = NULL; 

    create1 = al_create_thread(input, NULL); 
    create2 = al_create_thread(timer, NULL); 

    al_start_thread(create1);
    al_start_thread(create2);

    while (!finished && !timeOut) {
   
    }

    al_destroy_thread(create1);
    al_destroy_thread(create2);

    if (finished) {
        cout << "\n\tCongratulations, Word Master! You completed the challenge before time ran out!\n";
        cout << result << endl;
    } else {
        cout << "\n\tThe sands of time have run out...\n";
        cout << result << endl;
    }

    return 0; 
}

void * input(ALLEGRO_THREAD *ptr, void *arg) {
    result = game.playGame();
    if (!timeOut) {
        finished = true;
    }
    return NULL;
}
// A pointer to a function that starts time rand checks the change in finished, which is in the input thread. 
void * timer(ALLEGRO_THREAD *ptr, void *arg) {
    time_t startTime, currentTime; //times used to measure elapsed time
    startTime = time (NULL); 
    currentTime = time (NULL); 
    while (currentTime - startTime < 10 && !finished) { 
        currentTime = time (NULL); 
    }
    timeOut = true; 
    return NULL; 
}