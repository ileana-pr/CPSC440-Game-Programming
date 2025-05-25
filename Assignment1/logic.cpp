#include "logic.h"

logic::logic()
{   
    //open the file 
    //use a loop to read one line at a time 
    //store the line you read inside word[i]
    //take the word that you read in and scramble it and store in scrambleWord[i] 
    word = ""; 
    scramble = ""; 
    for (int i=0; i<100; i++)
        words[i] = ""; 
        //no deconstructor is needed because no dynamic memory has been created 
}
//return type className:: class Function name(parameters) 
void logic::setWord(string newWord) {
    word = newWord; 
}

string logic::getWord() {
    return word; 
}