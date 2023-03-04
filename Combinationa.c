#include<stdio.h>
#include<stdlib.h>

int GetRandom(int min,int max)// Hàm lấy random các số từ min đến max
{
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int checkRandom(int chosen[], int j, int r)
{
    for(int i = 0; i <= j; i++)
    {
        if(chosen[i] == r) return 0;
    }
    return 1;
}

void main()
{
    printf("\nIn this program, first you will enter a number of elements in the array");
    printf("\nThen, you will enter each element of the array one by one");
    printf("\nAfter that, enter the number of cobinations you want");
    printf("\nAfter that, output will be the chosen number of random combinations of the original array"); 
    int n, x;
    printf("\n********************************\nInput number of element: ");
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++)
    {
        printf(" E%d: ", i+1);
        scanf("%d", &a[i]);
    }
    printf("Input number of combinations: ");
    scanf("%d", &x);
    printf(" Com 0%-3s", ":");
    for(int i = 0; i < n; i++) printf("%-3d", a[i]);
    srand((unsigned int)time(NULL));
    for(int i = 0; i < x; i++)
    {
        printf("\n Com %d%-3s", i+1,":");
        int chosen[n]; 
        int j=0;
        while(j < n)
        {
            int r = GetRandom(0, n-1);
            if(checkRandom(chosen, j, r) == 1)
            {
                chosen[j] = r;
                printf("%-3d", a[r]);
                j++;
            }
        }
        getch();
    }
}