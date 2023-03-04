#include <stdio.h>
//calculate average
int main()
{
    int a, b, c;
    float avg;
    printf("Enter three numbers: ");
    scanf("%d %d %d", &a, &b, &c);
    avg = (a + b + c) / 3.0;
    printf("Average = %.2f", avg);
    return 0;
}