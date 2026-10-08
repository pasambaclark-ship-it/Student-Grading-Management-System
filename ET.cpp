#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct expense {
    string description;
    double amount;
    string category;
};

void seperator(int length) {
    cout << string(length, '*') << endl;
}

int main() {
    vector<expense> exp;
    int menu;
    double sum;

    seperator(100);
    cout << "1. Add Expense" << endl;
    cout << "2. View All Expense" << endl;
    cout << "3. Search Expense by Category" << endl;
    cout << "4. Calculate Total Spent" << endl;
    cout << "5. Exit Program" << endl;

do {
    cout << "Enter Your Choice: ";
    cin >> menu;
    cin.clear();
    cin.ignore(1000, '\n'); 
    seperator(100);

    switch (menu) {

        case 1: {
            expense exps;
            cout << "Enter Description: ";
            getline(cin, exps.description);
            cout << endl;

            cout << "Enter Amount: ";
            cin >> exps.amount;
            cout << endl;

             cin.ignore(1000, '\n');

            cout << "Enter Category: ";
            getline (cin, exps.category);
            cout << endl;
            exp.push_back(exps); 

            cout << "Expense added successfully!" << endl;
            seperator(100);
            break;
        }

        case 2: {
            if (exp.empty()) {
                cout << "No Item has been Added so far." << endl;
                seperator(100);
            } else {
                cout << "Expenses: " << endl;

                for (size_t i=0; i <exp.size(); i++) {
                    cout << i + 1 << ". " << exp[i].description <<" | " << exp[i].amount << " | " << exp[i].category << endl;
        
                }
                 seperator(100);
            }
            break;
        }

                case 3: {
            if (exp.empty()) {
                cout << "No Item has been Added so far." << endl;
                seperator(100);
            } else { 
                string searchCategory;
                bool found = false;
                
                cout << "Enter Category to Search: "; 
                getline(cin, searchCategory); 
                cout << endl; 

                cout << "--- Search Results ---" << endl;
                
                for (size_t i = 0; i < exp.size(); i++) {

                    if (exp[i].category == searchCategory) {
                        cout << i + 1 << ". " << exp[i].description 
                             << " | " << exp[i].amount 
                             << " | " << exp[i].category << endl;
                        found = true; 
                        
                    }
                }
                 seperator(100);

                if (!found) {
                    cout << "No expenses found under the category: " << searchCategory << endl;
                    seperator(100);
                }
            }
            break;
        }

              case 4: {
            sum = 0.0; 

            if (exp.empty()) {
                cout << "No items have been added so far. Total spent is 0." << endl;
            } else {
              
                for (size_t i = 0; i < exp.size(); i++) {
                    sum += exp[i].amount;
                }

               
                cout << "Total Spent: " << sum << endl;
            }
            
            seperator(100);
            break;
        }


        case 5: {
            cout << "Exiting Program..." << endl;
            seperator(100);
            break;
        }

        default:
        cout << "Invalid Choice!" << endl;
        cin.clear();
        cin.ignore();
        seperator(100);
        break;
        }


    }while (menu !=5 );

return 0;
}



