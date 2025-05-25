#include <string>
using std::string;

class logic{ 
    public: 
        logic(); 
        //setWord will update the private variable word with an input from main program
        //return nothing 
        void setWord(string newWord);
        //getWord takes the word from  private variable and returns to main program
        //returns a string  
        string getWord(); 

        void readFile(string fileName); 
        string getFirstScrambledWord(); //get from words array and then scramble the word and return the scrambled word 

private: 
    string word;
    string scramble; 
    string words[100]; 
    string scrambledWord[100]; 
};
//constructor className::className 
