#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct student {
    string name;
    string id;
    vector<double> grades;
};

void seperator(int length) {
    cout << string(length, '-') << endl;
}

int main() {
    vector<student> data;
    int menu;
    double sum;

    seperator(80);
    cout << "1. Add Student" << endl;
    cout << "2. Add Grades" << endl;
    cout << "3. View All Students" << endl;
    cout << "4. Search Student by ID" << endl;
    cout << "5. Calculate Class Average" << endl;
    cout << "6. Exit Program" << endl;
    seperator(80);

    do {
        cout << "Enter Your Choice: ";
        cin >> menu;
        cin.ignore(1000, '\n');

        switch (menu) {
            case 1: {
                student s;
                cout << "Enter Student Name: ";
                getline(cin, s.name);

                cout << "Enter Student ID: ";
                getline(cin, s.id);

                data.push_back(s);
                cout << "Student Added Successfully!" << endl;
                seperator(80);
                break;
            }

            case 2: {
                string searchid;
                cout << "Enter Student ID: ";
                getline(cin, searchid);

                bool found = false;
                for (size_t i = 0; i < data.size(); i++) {
                    if (data[i].id == searchid) {
                        double grade;
                        cout << "Enter Grade for Pre-Calculus: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for Basic Calculus: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for General Biology: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for General Chemistry: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for General Physics: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for Disaster Risk Reduction and Management: ";
                        cin >> grade; data[i].grades.push_back(grade);
                        cout << "Enter Grade for Practical Research: ";
                        cin >> grade; data[i].grades.push_back(grade);

                        cin.ignore(1000, '\n');
                        cout << "Grades Added Successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student ID doesn't exist in the system." << endl;
                }
                seperator(80);
                break;
            }

            case 3: {
                if (data.empty()) {
                    cout << "No Students have been Added Yet." << endl;
                } else {
                    cout << "--- Student List ---" << endl;
                    for (size_t i = 0; i < data.size(); i++) {
                        cout << i + 1 << ". " << data[i].name << " | ID: " << data[i].id << endl;
                        if (!data[i].grades.empty()) {
                            double sum = 0;
                            for (size_t j = 0; j < data[i].grades.size(); j++) {
                                sum += data[i].grades[j];
                            }
                            double avg = sum / data[i].grades.size();
                            cout << "   Average: " << avg << endl;
                        }
                    }
                }
                seperator(80);
                break;
            }

            case 4: {
                string searchid;
                cout << "Enter Student ID to Search: ";
                getline(cin, searchid);

                bool found = false;
                for (size_t i = 0; i < data.size(); i++) {
                    if (data[i].id == searchid) {
                        cout << "Student Found: " << data[i].name << " | ID: " << data[i].id << endl;
                        if (!data[i].grades.empty()) {
                            double sum = 0;
                            for (size_t j = 0; j < data[i].grades.size(); j++) {
                                sum += data[i].grades[j];
                            }
                            double avg = sum / data[i].grades.size();
                            cout << "Grades Count: " << data[i].grades.size() << endl;
                            cout << "Average: " << avg << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student ID does not exist!" << endl;
                }
                seperator(80);
                break;
            }

            case 5: {
                sum = 0.0;
                int totalgrade = 0;

                if (data.empty()) {
                    cout << "No Students to Calculate Average." << endl;
                } else {
                    for (size_t i = 0; i < data.size(); i++) {
                        for (size_t j = 0; j < data[i].grades.size(); j++) {
                            sum += data[i].grades[j];
                            totalgrade++;
                        }
                    }
                    if (totalgrade > 0) {
                        cout << "Class Average: " << (sum / totalgrade) << endl;
                    } else {
                        cout << "No Grades Entered Yet." << endl;
                    }
                }
                seperator(80);
                break;
            }

            case 6: {
                cout << "Exiting Program..." << endl;
                seperator(80);
                break;
            }

            default: {
                cout << "Invalid Choice!" << endl;
                seperator(80);
                break;
            }
        }

    } while (menu != 6);

    return 0;
}