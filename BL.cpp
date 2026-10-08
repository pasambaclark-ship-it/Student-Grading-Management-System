#include <iostream>
#include <string>
#include <vector>
using namespace std;


void seperator(int length) {
    cout << string(length, '*') << endl;
}


int main () {

    int menu;
    string title;
    vector<string> history;
    seperator(50);

cout << "---Book Library---" << endl;
cout << "1." "Add Books" << endl;
cout << "2." "View Books" << endl;
cout << "3." "Search Books" << endl;
cout << "4." "Exit" << endl;

do{
cout << "Enter Choice: ";
cin >> menu;
cin.clear();
cin.ignore(1000, '\n');

    switch (menu) {

        case 1:
        cout << "Enter Book Title: ";
        getline(cin, title);
        history.push_back(title);
        cout << "Book Added Successfully" << endl;
        seperator(50);
        break;

        case 2:
        if (history.empty()){
            cout << "No Books have been added yet." << endl;
            seperator(50);
        } else {
            cout << "Books in Library" << endl;

            for (int i = 0; i < history.size(); i++) {
                cout << i + 1 << ". " << history[i] << endl;
                seperator(50);
            }
        }
        break;

        case 3: {
        cout << "Enter Book title to search: ";
        getline(cin, title);

        bool found=false;
        for (int i = 0; i < history.size(); i++) {
            if (history[i] == title) {
            cout << "Book Found: " << history[i] << endl;
            found = true;
            break;
            }
        }
            if (!found) {
                cout << "Book not Found." << endl;
            }
        seperator(50);
        break;
        }

        case 4:
        cout << "Exiting Program..." << endl;
        break;

        default:
        cout << "Invalid Choice." << endl;
        cin.clear();
        cin.ignore();
        break;

    }


} while (menu !=4);

return 0;

}

