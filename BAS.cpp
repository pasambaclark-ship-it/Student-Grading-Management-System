#include <iostream>
#include <string>
#include <vector>
using namespace std;

void printseperator(int length) {
    cout << string(length, '*') << endl;
}

int main () {
    int Menu;
    double Balance = 0.00;
    double Depo = 0.00;
    double Withdraw = 0.00;
    vector<string> history;

    cout << "1"". Deposit Money" << endl;
    cout << "2"". Withdraw Money" << endl;
    cout << "3"". Check Transaction History" << endl;
    cout << "4"". Exit" << endl;
    printseperator (50);

do {
    
         cout << "Input Choice Number: "; 
         cin >> Menu;
         cin.clear();
         cin.ignore();
    
         

        switch (Menu) {

            case 1:
            cout << "Input the amount: ";
            cin >> Depo;
              if (Depo > 0){
                Balance += Depo;
            cout << "You Deposited: " << Depo << " Your Balance is: " << Balance << endl;
            printseperator (50);
            history.push_back("Deposited: " + to_string(Balance));
              } else {
                cout << "Invalid Deposit Amount." << endl;
                printseperator (50);
              }
            break;

            case 2:
            cout << "Input the amount: ";
            cin >> Withdraw;
             if (Withdraw > 0 && Withdraw <= Balance) {
                Balance -= Withdraw;
            cout << "You Withdrew: " << Withdraw << " Your Balance is: " << Balance << endl;
            printseperator (50);
            history.push_back("Withdrew: " + to_string(Balance));
              } else {
                cout << "Invalid Withdrew Amount." << endl;
                printseperator (50);
              }
            break;


            case 3:
              if (history.empty()) {
                cout << "No Transactions has been done." << endl;
                printseperator (50);
              } else {
                for (int i = 0; i < history.size(); i++) {
                    cout << i + 1 << ". " << history[i] << endl;
                    printseperator (50);
                }
              }
              break;


            case 4:
            cout << "Exiting Program...";
            break;


        }
    } while (Menu != 4);

return 0;

}