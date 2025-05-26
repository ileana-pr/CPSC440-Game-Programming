#include <fstream>
#include <iostream>
using namespace std;
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

void logic::readFile(string fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }
    string temp;
    while (file >> temp) {
        int len = temp.length();
        if ((len == 4 || len == 5) && count_four_five < 100) {
            four_five[count_four_five++] = temp;
        } else if ((len == 6 || len == 7) && count_six_seven < 100) {
            six_seven[count_six_seven++] = temp;
        } else if (len >= 8 && count_eight_plus < 100) {
            eight_plus[count_eight_plus++] = temp;
        }
    }
    file.close();
}