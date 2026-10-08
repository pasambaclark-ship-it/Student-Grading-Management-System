#include <iostream>
#include <string>
using namespace std;

int main () {
    string operation;
    int op;
    double celsius= 0.0;
    double farenheit= 0.0;
    int number;


    cout << "Welcome to the Menu-Diven Utility" << endl;
    cout << "If you want to start type (Continue): ";
     if (operation == "Continue") {
        cout << "Exiting Program." << endl;
    }
    cin >> operation;
   


cout << "1" << ". Convert Celsuis to Farenheit" << endl;
cout << "2" << ". Find if a number is Even or Odd" << endl;
cout << "3" << ". Exit" << endl;
cout << "Choose a Number" << endl;
cin >> op;

        switch (op) {
            case 1:
            cout << "Give the Value of Celsius: ";
            cin >> celsius;
                    farenheit = (celsius*9)/5 + 32;
                    cout << celsius << " = " << farenheit;
            break; 

            case 2:
            cout << "Give a Number: ";
            cin >> number;
                    cout <<  (number % 2 == 0 ? "Even" : "Odd");
            break; 

            case 3:
            cout << "Exiting Porgram...";
            break; 

            default: 
                cout << "Invalid Choice";
            }
       
     return 0;

}   
