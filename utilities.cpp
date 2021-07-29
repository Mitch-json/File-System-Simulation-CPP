#include <iostream>
#include <vector>
#include <sstream>


using namespace std;

// DO NOT MODIFY THIS FILE

// Utility function to split a string
vector<string> splitString(string input){
    stringstream ss(input); //convert input into string stream

    vector<string> args;
    string temp_str;

    while(getline(ss, temp_str, ' ')){ //use space as delim for cutting string
      args.push_back(temp_str);
    }

    return args;
}

// Print welcoming display
void printWelcomeDisplay(){
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << "////// WELCOME TO MITCH'S COMMAND PROMPT SIMULATION //////////" << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl << endl;
}
