#include<iostream>
#include<math.h>

using namespace std;

int sum(unsigned long int tmp)
{
    int sum = 0;
    do
    {
        sum += tmp%10;
        tmp /= 10;
        if(tmp == 0) break;
    }while(1);
    return sum;
}

int main(){
    unsigned long int a, b, i;
    int max = 0;
    cin >> a >> b;
    for (i = 1; i*i<=a; ++i)
    {
        if (a % i == 0)
        {   
            if(b % i == 0)
            {
                if(sum(i) > max) max = sum(i);
            }
        }
        if (i != a/i)
        {
            unsigned long c = a/i;
            if(b % c == 0)
            {
                if(sum(c) > max) max = sum(c);
            }
        }
    }
    cout << max;
}