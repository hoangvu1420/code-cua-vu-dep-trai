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
    if (a < 0)
    {
        printf("a = ");
        printBinary(a);
        printf("\n(a>>1) = ");
        printBinary(a >> 1);
        printf("\n(a/2) = ");
        printBinary(a / 2);
        printf("\n");
        if ((a >> 1) == (a / 2))
            printf("The results are the same.\n");
        else
            printf("The results are different.\n");
        printf("---\n");
        printf("a = ");
        printBinary(a);
        printf("\n(a<<1) = ");
        printBinary(a << 1);
        printf("\n(a*2) = ");
        printBinary(a * 2);
        printf("\n");
        if ((a << 1) == (a * 2))
            printf("The results are the same.\n");
        else
            printf("The results are different.\n");
    }
    else
    {
        printf("a is not negative.\n");
    }
    return 0;
}