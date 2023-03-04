#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double a, b, result;
    cin >> a >> b;
    result = sqrt(abs(exp(a)) + pow(sin(b), 2));
    cout << fixed << setprecision(5) << result << endl;
    return 0;
}
