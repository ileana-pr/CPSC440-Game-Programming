#include <fstream>
#include <iostream>
using namespace std;
#include "logic.h"
#include <algorithm>
#include <random>

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

void logic::introduction() {
    cout << "\nWelcome to the Word Scramble Game!" << endl;
    cout << "You will be given 5 scrambled words to solve." << endl;
    cout << "- The first two words are 4 or 5 letters long." << endl;
    cout << "- The next two words are 6 or 7 letters long." << endl;
    cout << "- The last word is 8 or more letters long." << endl;
    cout << "You have 60 seconds to solve all 5 words!" << endl;
    cout << "Type your guess and press Enter for each word." << endl;
    cout << "Good luck!\n" << endl;
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

string logic::playGame() {
    int correct = 0;
    string guess;

    // shuffle arrays so the first two words are random each time
    random_device rd;
    mt19937 g(rd());
    shuffle(four_five, four_five + count_four_five, g);
    shuffle(six_seven, six_seven + count_six_seven, g);
    shuffle(eight_plus, eight_plus + count_eight_plus, g);

    // four_five
    for (int i = 0; i < 2 && i < count_four_five; ++i) {
        string original = four_five[i];
        string scrambled = scrambler(original);
        cout << "Unscramble this word: " << scrambled << endl;
        cin >> guess;
        if (guess == original) {
            cout << "Correct!\n";
            correct++;
        } else {
            cout << "WRONG\n";
        }
    }

    //six_seven
    for (int i = 0; i < 2 && i < count_six_seven; ++i) {
        string original = six_seven[i];
        string scrambled = scrambler(original);
        cout << "Unscramble this word: " << scrambled << endl;
        cin >> guess;
        if (guess == original) {
            cout << "Correct!\n";
            correct++;
        } else {
            cout << "WRONG\n";
        }
    }

    // eight_plus
    if (count_eight_plus > 0) {
        string original = eight_plus[0];
        string scrambled = scrambler(original);
        cout << "Unscramble this word: " << scrambled << endl;
        cin >> guess;
        if (guess == original) {
            cout << "Correct!\n";
            correct++;
        } else {
            cout << "WRONG\n";
        }
    }

}