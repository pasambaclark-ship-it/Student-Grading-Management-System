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
    cout << string(length, '*') << endl;
}

int main() {
    vector<student> studs;
    int menu;
    double sum;

    seperator(100);
    cout << "1. Add Student" << endl;
    cout << "2. Add Grades" << endl;
    cout << "3. View All Students" << endl;
    cout << "4. Search Student by ID" << endl;
    cout << "5. Calculate Class Average" << endl;
    cout << "6. Exit Program" << endl;

    do {
        cout << "Enter Your Choice: ";
        cin >> menu;
        cin.clear();
        cin.ignore(1000, '\n');
        seperator(100);

        switch (menu) {
            case 1: {
                student s;
                cout << "Enter Student Name: ";
                getline(cin, s.name);
                cout << endl;

                cout << "Enter Student ID: ";
                getline(cin, s.id);
                cout << endl;

                studs.push_back(s);
                cout << "Student added successfully!" << endl;
                seperator(100);
                break;
            }

            case 2: {
                string searchID;
                cout << "Enter Student ID: ";
                getline(cin, searchID);

                bool found = false;
                for (size_t i = 0; i < studs.size(); i++) {
                    if (studs[i].id == searchID) {
                        double grade;
                        cout << "Enter Grade: ";
                        cin >> grade;
                        cin.ignore(1000, '\n');
                        studs[i].grades.push_back(grade);
                        cout << "Grade added successfully!" << endl;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student ID not found. Please add the student first." << endl;
                }
                seperator(100);
                break;
            }

            case 3: {
                if (studs.empty()) {
                    cout << "No students have been added yet." << endl;
                } else {
                    cout << "--- Student List ---" << endl;
                    for (size_t i = 0; i < studs.size(); i++) {
                        cout << i + 1 << ". " << studs[i].name << " | ID: " << studs[i].id << endl;
                        if (!studs[i].grades.empty()) {
                            double sum = 0;
                            for (size_t j = 0; j < studs[i].grades.size(); j++) {
                                sum += studs[i].grades[j];
                            }
                            double avg = sum / studs[i].grades.size();
                            cout << "   Average: " << avg << endl;
                        }
                    }
                }
                seperator(100);
                break;
            }

            case 4: {
                string searchID;
                cout << "Enter Student ID to Search: ";
                getline(cin, searchID);

                bool found = false;
                for (size_t i = 0; i < studs.size(); i++) {
                    if (studs[i].id == searchID) {
                        cout << "Student Found: " << studs[i].name << " | ID: " << studs[i].id << endl;
                        if (!studs[i].grades.empty()) {
                            double sum = 0;
                            for (size_t j = 0; j < studs[i].grades.size(); j++) {
                                sum += studs[i].grades[j];
                            }
                            double avg = sum / studs[i].grades.size();
                            cout << "Grades Count: " << studs[i].grades.size() << endl;
                            cout << "Average: " << avg << endl;
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Student not found." << endl;
                }
                seperator(100);
                break;
            }

            case 5: {
                sum = 0.0;
                int totalGrades = 0;

                if (studs.empty()) {
                    cout << "No students to calculate average." << endl;
                } else {
                    for (size_t i = 0; i < studs.size(); i++) {
                        for (size_t j = 0; j < studs[i].grades.size(); j++) {
                            sum += studs[i].grades[j];
                            totalGrades++;
                        }
                    }
                    if (totalGrades > 0) {
                        cout << "Class Average: " << (sum / totalGrades) << endl;
                    } else {
                        cout << "No grades entered yet." << endl;
                    }
                }
                seperator(100);
                break;
            }

            case 6: {
                cout << "Exiting Program..." << endl;
                seperator(100);
                break;
            }

            default: {
                cout << "Invalid Choice!" << endl;
                seperator(100);
                break;
            }
        }

    } while (menu != 6);

    return 0;
}
