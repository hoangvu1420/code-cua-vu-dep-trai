#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;


int main()
{
    FILE *ff = fopen("tess.txt", "r");
    string s;
    char c;
    int a[5];
    // cout << c << endl;
    while(1)
    {
        char ss[50];
        c = fgetc(ff);
        if(c == EOF) break;
        if(c == ' ')
        {
            fgets(ss, sizeof(s),ff);
            cout << ss;
        }
        // cout << c;
    } 
    // cout << c;
    fclose(ff);
    return 0;
}

// #include <iostream>
// #include <fstream>
// #include <iomanip>

// using namespace std;

// int main()
// {
//     string a;
// 	cin >> setw(2) >> a;
//     // cout << a;
//     stringstream s;
//     s << a;
//     int n;
//     s >> n;
    
//     cout << n;
// 	return 0;
// }