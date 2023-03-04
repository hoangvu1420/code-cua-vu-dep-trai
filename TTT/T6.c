#include <stdio.h>

void printBinary(int num)
{
    if (num > 1)
        printBinary(num / 2);
    printf("%d", num % 2);
}

int main(void)
{
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("a = ");
    printBinary(a);
    printf("\n-a = ");
    printBinary(-a);
    printf("\n");
    return 0;
}