#include<iostream>
#include<queue>
#include<iomanip>

using namespace std;
void sinh_xau(int n)
{
    vector<string> bin;
    queue<string> q;
    q.push("1");
    string top;
    while(1) 
    {
        top = q.front();
        if(top.length() > 2) break;
        q.pop();
        q.push(top + "0");
        q.push(top + "1");
        bin.push_back(top + "0");
        bin.push_back(top + "1");
    }
    cout << setfill('0');
    cout << setw(n) << right << "0" << endl;
    for(string x : bin)
    {   
        cout << setw(n) << right << x << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    sinh_xau(n);
    return 0;
}