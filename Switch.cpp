#include <iostream>
using namespace std;

int main () {

    int day;
    bool correct = false;
    cout << "Give me a number to represent the Day of the Week" << endl;
    

while (correct == false) {

    cin >> day;
    switch (day) {

        case 1: 
        cout << "Monday";
        correct = true;
        break;

        case 2: 
        cout << "Tuesday";
        correct = true;
        break;

        case 3: 
        cout << "Wednesday";
        correct = true;
        break;

        case 4: 
        cout << "Thursday";
        correct = true;
        break;

        case 5: 
        cout << "Friday";
        correct = true;
        break;

        case 6: 
        cout << "Saturday";
        correct = true;
        break;

        case 7: 
        cout << "Sunday";
        correct = true;
        break;

    }

    if (day > 7 || day < 1) {
        cout << "Invalid Input, try again";
    }
}
return 0;

}