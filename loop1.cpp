#include <iostream>
using namespace std;

int main () {

    int num;
    bool correct = false;

cout << "Welcome to Prime Number Checker!" << endl;
cout << "Give an Integer" << endl;

    while (correct == false) {
        cin >> num;
            for (int i=2; i*i ; i++) {
                if (num % i == 0) {
                    correct= true;
                    break;
                }
            }

                if (correct) {
                    cout << "Prime Number";

                }
                else {
                    cout << "Not Prime Number";
                }
    } 
return 0;
}