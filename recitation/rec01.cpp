// rec01-start.cpp
// 2124 21S


#include <iostream>    // Tasks 3, 4, 5 and 6

#include <fstream>     // Task 4, 5 and 6
#include <string>      // Task 5
using namespace std;

int main() {
    // Task 3
    cout << "Task 3\n========\n";
    // Put code for Task 3 here
    cout << "Yay C++!!!\n";


    // Task 4
    cout << "Task 4\n========\n";
    // Put code for Task 4 here
    ifstream ifs("integers.txt");
    if (!ifs) {
       cerr << "Could not open the file.\n";
       exit(1);
    }
    int anInt;
    int total = 0;
    while (ifs >> anInt) {
        total += anInt;
    }
    cout << total << endl;
    ifs.close();

    // Task 5
    cout << "Task 5\n========\n";
    // Put code for Task 5 here
    ifstream ifs2("text.txt");
    if (!ifs2) {
       cerr << "Could not open the file.\n";
       exit(1);
    }
    string aStr;
    while (ifs2 >> aStr) {
        cout << aStr << endl;
    }
    ifs.close();
    

    // Task 6
    cout << "Task 6\n========\n";
    // Put code for Task 6 here

    ifstream ifs3("mixed.txt");
    if (!ifs3) {
       cerr << "Could not open the file.\n";
       exit(1);
    }
    string aStr2;
    int total2 = 0;
    while (ifs3 >> anInt) {
        total2 += anInt;
    }
    cout << total2 << endl;
    ifs.close();
    
}
