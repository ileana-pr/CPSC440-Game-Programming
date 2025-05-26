#include <string>
using std::string; 

class logic{ 
    public: 
        logic(); 
      
        void introduction(); 
        void readFile(string fileName); 
        string playGame(); 
        string scrambler(string word); 
    
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

 