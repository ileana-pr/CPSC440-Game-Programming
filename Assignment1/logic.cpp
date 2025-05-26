#include <fstream>
#include <iostream>
using namespace std;
#include "logic.h"
#include <algorithm>
#include <random>
extern bool timeOut;

logic::logic()
{
    word = "";
    scramble = "";
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
    random_device rd;
    mt19937 g(rd());
    shuffle(four_five, four_five + count_four_five, g);
    shuffle(six_seven, six_seven + count_six_seven, g);
    shuffle(eight_plus, eight_plus + count_eight_plus, g);
    for (int i = 0; i < 2 && i < count_four_five; ++i) {
        if (timeOut) break;
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
    for (int i = 0; i < 2 && i < count_six_seven; ++i) {
        if (timeOut) break;
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
    if (count_eight_plus > 0 && !timeOut) {
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
    string message;
    switch (correct) {
        case 5:
            message = "Genius! You have the mind of a word wizard! 🧙‍♂️";
            break;
        case 4:
            message = "Impressive! Your intellect is top-tier! 🧠";
            break;
        case 3:
            message = "Not bad! You have a sharp mind! 🧐";
            break;
        case 2:
            message = "Keep practicing! Your mind is warming up! 🔥";
            break;
        default:
            message = "Try again! The word scramble got the best of you this time! 😅";
            break;
    }
    return message;
}