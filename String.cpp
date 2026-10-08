#include <iostream>
#include <string>
using namespace std;

int main () {

    cout << "Welcome to Skyscope's Number Guessing game!" << endl;
    cout << "You need to Guess from number 1-10" << endl;
    cout << "Now, Let's begin" << endl;
    cout << "Firstly, Give me a number to start the game" << endl;
    cin >> number;
    int number;

    if (number==1){
        cout << "Wrong Number, Try again.";
    } 
    else if (number==2) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==3) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==4) {
        cout << "Congratulations!";
    }
     else if (number==5) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==6) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==7) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==8) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==9) {
        cout << "Wrong Number, Try again.";
    }
     else if (number==10) {
        cout << "Wrong Number, Try again.";
    }
    else {
        cout << "Invalid Number, Try again." << endl;
    }

    return 0;
}