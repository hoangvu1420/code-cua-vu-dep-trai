#include<iostream>
#include<math.h>
#include<time.h>

using namespace std;
typedef long long ll;
int main()
{

    int n,m; 
    // cout << "n, m ";
    cin >> n >> m;
    ll a[n+1][m+1];
    clock_t start, end;   // Khai báo biến thời gian
    double time_use;      // Thời gian sử dụng
    start = clock();  
    for(int i = 1; i<=n; i++)
        for (int j=1; j<=m; j++)
            cin >> a[i][j];
    ll prefix[n+1][m+1] = {0};
    for(int i=0; i<=n; i++)
        for (int j=0; j<=m; j++)
            prefix[i][j] = 0;
    for(int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            prefix[i][j] = prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1] + a[i][j];
    // for(int i=0; i<=n; i++)
    // {
    //     for (int j=0; j<=m; j++)
    //     {
    //         cout << prefix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    int q;
    // cout << "q "; 
    cin >> q;
    ll s[q];
    for(int i=0; i<q; i++)
    {
        int h1, h2, c1, c2;
        // cout << "h1 h2 c1 c2 ";
        cin >> h1 >> c1 >> h2 >> c2;
        // cout << prefix[h2][c2] << "-" << prefix[h2][c1-1] <<"-"<< prefix[h1-1][c2] <<"+"<< prefix[h1-1][c1-1] <<endl;
        s[i] = prefix[h2][c2] - prefix[h2][c1-1] - prefix[h1-1][c2] + prefix[h1-1][c1-1];
    }
    for(int i=0; i<q; i++)
        cout << s[i] << endl;
    end = clock();  // lấy thời gian sau khi thực hiện 
    time_use = (double)(end - start) / CLOCKS_PER_SEC;    //Tính thời gian sử dụng
    cout<<"\nTime: "<<time_use;
    return 0; 
}