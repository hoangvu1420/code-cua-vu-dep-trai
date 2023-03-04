#include<iostream>
using namespace std;

// //cách 1: tạo 1 vòng biên các phần từ bằng 0 bao quanh ma trận nhập vào. Từng phần tử của ma trận thay thế sẽ được tính bằng 
// tổng một hình vuông 3x3 của ma trận nhập vào.
// int main()
// {
//     int q; cin >> q;
//     while(q--)
//     {
//         int h, c;
//         cin >> h >> c;
//         int a[h+2][c+2], b[h][c];
//         for(int i=0; i<=h+1; i++)
//             for(int j=0; j<=c+1; j++)
//             {
//                 b[i][j] = 0;
//                 if(j == 0 || i == 0 || i == h+1 || j == c+1) a[i][j] = 0;
//                 else cin >> a[i][j];
//             }    
//        
//         for(int i=1; i<=h; i++)
//         {
//             for(int j=1; j<=c; j++)
//             {
//                 b[i][j] = a[i][j] + a[i+1][j] + a[i][j+1] + a[i-1][j] + 
//                 a[i][j-1] + a[i-1][j-1] + a[i+1][j+1] + a[i+1][j-1] + a[i-1][j+1];
//                 cout << " " << b[i][j] << " ";
//             }
//             cout << endl;
//         }
        
//     }
// }


// cách 2 khai báo 2 mảng int thể hiện độ chênh lệch của chỉ số hàng và cột của các phần tử trong hình vuông 3x3 bao quanh với hàng 
// và cột của phần tử đang xét. Sau đó cộng tổng hình vuông lại rồi gán vào từng phần tử của ma trận thay thế.
int x[9] = {-1,-1,-1,0,0,0,1,1,1};
int y[9] = {-1,0,1,-1,0,1,-1,0,1};
int main()
{
    int q; cin >> q;
    while(q--)
    {
        int h, c;
        cin >> h >> c;
        int a[h][c];
        for(int i=0; i<h; i++)
        {            
            for(int j=0; j<c; j++)
            {
                cin >> a[i][j];
            }
        }
        int rep[h][c];
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<c; j++)
            {
                int sum = 0;
                for(int k=0; k<9; k++)
                {
                    int it = i + x[k];
                    int jt = j + y[k];
                    if(it < 0 || jt < 0 || it >= h || jt >= c) continue;
                    else {
                        sum += a[it][jt];
                        // cout << a[it][jt];
                    } 
                }
                rep[i][j] = sum;
                cout << " " << rep[i][j] << " ";
            }
            cout << endl;
        }
    }
}