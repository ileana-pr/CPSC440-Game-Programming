#include <iostream>
#include<allegro5/allegro.h> 
#include "logic.cpp"

void *input(ALLEGRO_THREAD *ptr, void *arg); 
void *timer(ALLEGRO_THREAD *ptr, void *arg); 

logic game; //instance of logic 
bool finished = false; 
bool timeOut = false; 

int main() {

    game.introduction(); 
    // Read file into game.readFile() 
    game.readFile("dictionary.txt"); 
    
    ALLEGRO_THREAD *create1 = NULL, *create2 = NULL; 

    create1 = al_create_thread(input, NULL); 
    create2 = al_create_thread(timer, NULL); 

    while (!finished && !timeOut) { 
        if (!finished && !timeOut){ 
            al_start_thread(create1); 

            al_start_thread(create2); 
        }else { 
            al_destroy_thread (create1); 
            al_destroy_thread (create2); 
        }
        if(finished) {
            cout<<"\n\tUser entered input and that ended the program\n"; 
        } else {
            cout<<"\n\tTime ran out and that ended the program\n"; 
        }
    }

    return 0; 
}

void * input(ALLEGRO_THREAD *ptr, void *arg) {
    string result = game.playGame();
    cout << result << endl;
    finished = true;
    return NULL;
}
// A pointer to a function that starts time rand checks the change in finished, which is in the input thread. 
void * timer(ALLEGRO_THREAD *ptr, void *arg) {
    time_t startTime, currentTime; //times used to measure elapsed time
    startTime = time (NULL); 
    currentTime = time (NULL); 
    while (currentTime - startTime < 60 && !finished) { 
        currentTime = time (NULL); 
    }
    timeOut = true; 
    return NULL; 
}