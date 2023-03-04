#include<iostream>

using namespace std;

int main()
{
    string ss;
    cin >> ss;
    int c = 1;
    for(int i = 0; i < ss.length(); i++)
    {
        if(ss[i] == ss[i+1])
        {
            c++;
        }
        else 
        {
            cout << ss[i] << c;
            c = 1;
        }
    }
}