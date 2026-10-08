#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct note{
    string description;
    bool complete;
};

void seperator(int length) {
    cout << string(length, '*') << endl;
}

int main() {
    vector<note> task;
    int menu;

seperator(50);
    cout << "1. Add Task" << endl;
    cout << "2. View All Task" << endl;
    cout << "3. Search Task" << endl;
    cout << "4. Mark Task as Completed" << endl;
    cout << "5. Exit Program" << endl;

do {
    cout << "Enter Your Choice: ";
    cin >> menu;
    cin.clear();
    cin.ignore(1000, '\n');
    seperator(50);

     switch (menu) {

        case 1: {
            note temp;
            cout << "Enter Task Description: ";
            getline(cin, temp.description);
            temp.complete = false;
            task.push_back(temp);
            cout << "Task have been Added Succesfully!" << endl;
            seperator(50);
            break;
        }

        case 2: {
            note temp;
            if (task.empty()) {
                cout << "No Task have been Added Yet." << endl;
                seperator(50);
            } else {
                cout << "Task: " << endl;

                for (size_t i=0; i<task.size(); i++) {
                    cout << i + 1 << ". " << task[i].description << "[" << (task[i].complete ? "Completed" : "Pending") << "]" << endl;
                    seperator(50);
                }
            }
            break;
        }

        case 3: {
            note temp;
            if (task.empty()) {
                cout << "No Task have been Added Yet." << endl;
                seperator(50);
            } else {
                string search_query;
                cout << "Enter a Task to Search: ";
                getline(cin, search_query);

                bool found= false;
                for (size_t i=0; i<task.size(); i++) {
                   if (task[i].description == search_query) {
                    cout << "Task Found #" << i + 1 << ": " << task[i].description << endl;
                    seperator(50);
                    found = true;
                    break;
                   }
                }
                if (!found) {
                    cout << "Task Do not Exist." << endl;
                    seperator(50);
                }
            }
            break;
        }

        case 4: {
            if (task.empty()) {
                cout << "No Task have been Added Yet." << endl;
                seperator(50);
            } else {
                int number;
                cout << "Enter Task Number : ";
                cin >> number;
                cin.clear();
                cin.ignore(1000, '\n');

                if (number > 0 && number <=task.size()) {
                    task[number - 1].complete = true;
                    cout <<  "Task marked as completed successfully!" << endl;
                    seperator(50);
                } else {
                        cout << "Invalid task number." << endl;
                        seperator(50);
                }
            }
            break;
        }

        case 5: {
        cout << "Exiting Program..." << endl;
        seperator(50);
        break;
        }
    }

} while (menu != 5);


return 0;
}
