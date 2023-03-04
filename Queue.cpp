#include<iostream>
#include<fstream>
#include<iomanip>
#include<queue>
using namespace std;
using ll = long long;

vector<ll> arr;
ll result[101];
int c = 0;
void Que()
{
    queue<string> que;
    que.push("9");
    
    string top;
    while(top.length() <= 10)
    {
        top = que.front();
        que.pop();
        que.push(top + "0");
        que.push(top + "9");
        ll x, y;
        stringstream s1, s2;
        s1 << top + "0";
        s2 << top + "9";
        s1 >> x;
        s2 >> y;
        arr.push_back(x);
        arr.push_back(y);
    }
    for(int i=1; i<101; i++)
    {
        for(ll x : arr)
        {
            if(x % i == 0)
            {
                result[i] = x;
                c++;
                break;
            }
        }
    }
    // cout << "\n" << c;
}

int main()
{
    Que();
    int n; cin >> n;
    cout << result[n];
    return 0;
}
