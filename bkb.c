#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

int GetRandom(int min,int max)// Hàm lấy random các số từ min đến max
{
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

void main()
{
    int d = 0;
    int w = 0, l = 0, h = 0;
    srand((unsigned int)time(NULL));
    while(1)
    {
        char s[4];
        int n, m, x;
        printf("\n********************************\n");
        printf("Luot choi: %d\n", d+1);
        printf("Hay chon (Bua, Keo, Bao): "); scanf("%s", &s);
        if(strcmp(s, "Bua") == 0) n = 1; else if(strcmp(s, "Keo") == 0) n = 2; else if(strcmp(s, "Bao") == 0) n = 3;
        x = GetRandom(1, 300);
        // printf("%d\n", x);
        if(x >= 1 && x <= 100) m = 1;
        else if(x >= 101 && x <= 200) m = 2;
        else if(x >= 201 && x <= 300) m = 3;
        // printf("%d\n", m);
        if(m == n) 
        {
            printf("\nHOA\n");
            h++;
        }
        else if ((m == 1 && n == 2) || (m == 2 && n == 3) || (m == 3 && n == 1)) 
        {
            printf("\nBAN THUA\n");
            l++;
        }
        else
        {
            printf("\nBAN THANG\n");
            w++;
        }
        printf("\nSo lan thang: %d", w);
        printf("\nSo lan thua: %d", l);
        printf("\nSo lan hoa: %d", h);
        d++;
        if(d%10 == 0) {
            char sw;
            printf("\nChoi chan chua? (Y/N): ");
            scanf("%c", &sw);
            if(sw == 'Y') break;
        }
    }
    printf("\n%d\n", d);
}

