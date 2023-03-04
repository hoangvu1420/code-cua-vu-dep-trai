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
    printf("The binary representation of %d is: ", a);
    print_binary(a);
    printf("\n");
    return 0;
}
