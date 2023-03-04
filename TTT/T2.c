#include <stdio.h>

void printBinary(int num)
{
    if (num > 1)
        printBinary(num/2);
    printf("%d", num % 2);
}

int main()
{
    int a;
    printf("Enter a number: ");
    scanf("%d", &a);
    printBinary(a);
    printf("\n");
    printf("(a>>1) = "); 
    printBinary(a>>1);
    printf("\n");
    printf("(a/2) = "); 
    printBinary(a/2);
    printf("\n");
    if ((a>>1) == (a/2))
        printf("The results are the same.");
    else
        printf("The results are different.");  
    return 0;
}