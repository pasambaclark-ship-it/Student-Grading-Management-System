#include <iostream>
using namespace std;

int main () {

    bool correct= false;
    int num;
cout << "Welcome to SkyScope's Multiplication table" << endl;
cout << "Enter a Number: ";

while (correct== false) {
    cin >> num;

    for (int i =0; i < 11; i++) {
        correct= true;
        cout << num << "x" << i << "=" << num*i << endl;
        
    }

}

return 0;
    
}