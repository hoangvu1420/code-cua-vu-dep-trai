#include<stdio.h>

const int n = 5;
void buble_sort(int a[])
{
    int sw;
    do
    {
        sw = 0;
        for(int i=0; i<n; i++)
        {
            if(a[i] > a[i+1])
            {
                int tmp = a[i];
                a[i] = a[i+1];
                a[i+1] = tmp;
                sw = 1;
            }
        }
    } while (sw == 1);
}

void selection_sort(int a[])
{
    for(int i=0; i<n; i++)
    {
        int min = i;
        for(int j=i+1; j<n; j++)
        {
            if(a[min] > a[j])
                min = j;
        }
        int tmp = a[min];
        a[min] = a[i];
        a[i] = tmp;
    }
}

void insertion_sort(int a[])
{
    for(int i=1; i<n; i++)
    {
        int last = a[i];
        int j = i;
        while(j > 0 && a[j-1] > last)
        {
            a[j] = a[j-1];
            j--;
        }
        a[j] = last;
    }
}
void merge(int a[], int l, int m, int r){
    int n1 = m - l + 1, n2 = r - m;

}
int main()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    // buble_sort(a);
    // selection_sort(a);
    insertion_sort(a);
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    return 0;
}