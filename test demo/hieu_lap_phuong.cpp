#include<iostream>
#include<math.h>

using namespace std;

bool check(long long i)
{
    if(i == 0 || i == 1) return 0;
    for(int j=2; j*j<=i; j++)
    {
        if(i%j == 0) return false;
        if(j != i/j)
        {
            int x = i/j;
            if(i%x == 0) return false;
        }
    }
    return true;
}

int main()
{
    int q;
    cin >> q;
    int p = q;
    int ar[q];
    for(int i=0; i<q; i++)
    {
        long long a;
        cin >> a;
        int count = 0;
        for(int i=0; i<=a; i++)
        {
            int x = int(pow(a,3) - pow(i,3));
            if(check(x)) count++;
        }
        ar[i] = count;
    }
    for(int i=0; i<p; i++)
    {
        cout << ar[i] << endl;
    }
    return 0;
}
