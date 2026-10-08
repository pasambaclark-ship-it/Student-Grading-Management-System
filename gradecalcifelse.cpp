#include <iostream>
#include <string>
using namespace std;

int main () {

    int physics;
    int genbio;
    int genchem;
    int research;
    int entrep;
    int pe;
    int philo;
    int total;
    int gwa;

cout << "This is a Grade Calculator" << endl;
cout << "Please input your Grades in every subject" << endl;

cout << "Physics" << endl;
cin >> physics;

cout << "General Biology" << endl;
cin >> genbio;

cout << "General Chemistry" << endl;
cin >> genchem;

cout << "Practical Research" << endl;
cin >> research;

cout << "Entrepreneurship" << endl;
cin >> entrep;

cout << "P.E" << endl;
cin >> pe;

cout << "Philosophy" << endl;
cin >> philo;

total= physics + genbio + genchem + research + entrep + pe + philo;
gwa = total/7;

cout << "Your GWA is: " << gwa << endl;

    if (gwa >= 90 && gwa <= 100 ) {
    cout << "Your Final Grade Assessment is: " << "A";
    }   
    else if (gwa >=80 && gwa <= 89) {
        cout << "Your Final Grade Assessment is: " << "B";
    }
    else if (gwa >=70 && gwa <= 79) {
        cout << "Your Final Grade Assessment is: " << "C";
    }
    else if (gwa >=60 && gwa <= 69) {
        cout << "Your Final Grade Assessment is: " << "D";
    }
    else {
        cout << "FAILED, Focus More on STUDYING!";
    }


return 0;


}