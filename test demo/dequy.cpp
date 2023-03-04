#include<iostream>
#include<sstream>  
#include <iomanip>

using namespace std;
using std::string;

int giaiThua (int n) {
    if (n == 1) return 1;
    return n * giaiThua(n-1);
}

string decimal_to_bin(int decimal, string binary)
{
    if(decimal == 0) return binary;
    stringstream s;
    string ss;
    s << decimal%2;
    s >> ss;
    binary = ss + binary;
    return decimal_to_bin(decimal/2, binary);
}

int main(){
    int n;
    // cout << "Decimal: ";
    cin >> n;
    cout << setfill('-');
    // cout << "Binary: " << setw(16) << right << decimal_to_bin(n, "");
    cout << giaiThua(n) << endl;
    return 0;
}