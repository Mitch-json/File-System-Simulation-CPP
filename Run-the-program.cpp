#include "utilities.cpp"
#include "fileSystemSim.cpp"

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

int main(){
    printWelcomeDisplay();

    // Create the root.
    //Directory * pwd = new Directory(); // pwd stands for present working directory
    // At the beginning the pwd is the root. It is the only directory created, so far.
    Directory * pwd = new Directory();
    // Initialize some variables
    string input;
    vector<string> args;

    // A loop that will run until 'exit' is typed
    while(true){
        // Get a command from the user
        cout << "Mitch:" << pwd->getPath() << " $ "; // this mimics the Linux (ubuntu) command prompt
        getline(cin, input); // put the entire line onto input
        if(input == "exit") break;

        // Tokenize the input
        args = splitString(input);

        // Run the command
        pwd = runCommand(pwd, args);

    }

    return 0;
}
