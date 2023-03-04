#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<math.h>

void sum(int n)
{
    if(n <= 100) 
    {
        printf("%d ",n);
        sum(n+1);
    }
    else return;
}//Đệ quy in ra các số từ n đến 100

int sum1(int n)
{
    if(n == 100) return 100;
    else return n+sum1(n+1);
}//Đệ quy tính tổng các số từ n đến 100

int main()
{
    int n;
    printf("n = "); scanf("%d", &n);
    sum(n);
    printf("\n");
    printf("sum1 = %d", sum1(n));
    return 0;
}