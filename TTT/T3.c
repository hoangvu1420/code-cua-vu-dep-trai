#include <stdio.h>

void print_binary(int num)
{
    if (num > 1)
        print_binary(num / 2);
    printf("%d", num % 2);
}

int main()
{
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);
    printf("a = ");
    print_binary(a);
    printf("\n");
    printf("(a<<1) = ");
    print_binary(a << 1);
    printf("\n");
    printf("(a*2) = ");
    print_binary(a*2);
    printf("\n");
    if ((a << 1) == (a * 2))
        printf("The results are the same.\n");
    else
        printf("The results are different.\n");
    return 0;
}