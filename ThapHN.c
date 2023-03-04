#include<stdio.h>

void Tower(int n , char a, char b, char c ){
    // printf("n%d ",n);
    if(n==1){
        printf("\n%c----->%c\n", a, c);
        return;
    }
    // printf("| ");
    Tower(n-1, a, c, b);
    // printf("|| ");
    Tower(1, a, b, c);
    // printf("||| ");
    Tower(n-1, b, a, c);
    } 
int main(){
    char a='A', b='B', c='C';
    int n;
    printf("Nhap n: "); scanf("%d", &n);    
    Tower(n,'A','B','C');
}