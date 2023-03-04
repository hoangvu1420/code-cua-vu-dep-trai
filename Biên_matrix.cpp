#include<iostream>
using namespace std;

int main()
{
    int h, c;
    cin >> h >> c;
    int a[h][c];
    for(int i=0; i<h; i++)
        for(int j=0; j<c; j++)
            cin >> a[i][j];
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<c; j++)
        {
            if(i == 0 || j == 0 || i == h-1 || j == c-1)
            {
                cout << a[i][j] << " ";
            }
            else cout << "  ";
        }
        cout << endl;
    }
}