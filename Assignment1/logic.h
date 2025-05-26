#include <string>
using std::string; 


class logic{ 
    public: 
        logic(); 
        //setWord will update the private variable word with an input from main program
        //return nothing 
        void introduction(); 
        //provides user with basic introduction 
        void readFile(string fileName); 
        //reads file and saves words to array lists 
        string playGame(); 
        //carries out the actual word scrambling
        //returns: true if user wins and false if not
        string scrambler(string word); 
        //takes in a word and scrambles it
        //returns a scrambled version of the parameter
        void end(); 
        //displays the endgame information 

        void setWord(string newWord);
        //getWord takes the word from  private variable and returns to main program
        //returns a string  
        string getWord(); 

      
        


        string getFirstScrambledWord(); //get from words array and then scramble the word and return the scrambled word 

private: 
    int numCorrect;
    int smallWordLength;
    int mediumWordLength;
    int largeWordLength;
    string word;
    string scramble; 
    string words[100]; 
    string scrambledWord[100]; 
    string four_five[100];
    int count_four_five = 0;
    string six_seven[100];
    int count_six_seven = 0;
    string eight_plus[100];
    int count_eight_plus = 0;
};
//constructor className::className 

 