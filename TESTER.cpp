#include <cstdlib>
#include <iostream>

using namespace std;

int main () {
    int help;
    int randomNumber = rand() % 101;

    cout << randomNumber << endl;

    cin >> help;
    return 0;
}