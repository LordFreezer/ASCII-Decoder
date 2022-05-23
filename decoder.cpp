/*
ASCII Decoder For Online Pascal Compiler
by Chad Marshall
Created 5/22/2022
-----------------------------------------------------
Since I am leveraging CGI (Common Gateway Interface)
to allow C++ code to be my server side code, the Pascal
program that the user enters is saved in a text file as
a query string. The purpose of this c++ program is to 
decode the single line of query string back into a Pascal
program while maintaining the structure of the Pascal 
program.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// converts hex -> dec
int fromHex(string hex) {
    unsigned int x;
    stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return static_cast<int>(x);
}

// converts dec -> ascii
char toAscii(int x) {
    return static_cast<char>(x);
}


int main() {  
    string inLine,storage;

    // read and save query string (Pascal program) as C++ string
    ifstream myfile("example.txt");
    if (myfile.is_open()) {
        while (getline(myfile, inLine))
        {
            storage += inLine + "\n"; // should be single line
        }
        myfile.close();
    } else cout << "Unable to open file";

    // remove query string assignment
    storage = storage.substr(2, storage.length());
    

    for (int i = 0; i < storage.length(); i++) {
        // replace hex with ascii equivalent in query param
        if (storage[i] == '%') {
            string hex;
            hex.push_back(storage[i + 1]); 
            hex.push_back(storage[i + 2]);
            string replacement;
            replacement.push_back(toAscii(fromHex(hex)));
            storage.replace(i, 3, replacement);
        }
        // replace space in query peram
        if (storage[i] == '+') {
            storage.replace(i, 1, " ");
        }
    }
    cout << storage << endl;
}