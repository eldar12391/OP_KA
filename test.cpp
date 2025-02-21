#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    string myStr1 = "Привет";
    cout << setw(10) << myStr1[3] << endl;
    return 0;
}