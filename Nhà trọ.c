#include<stdio.h>
#include<string.h>
#include<math.h>


typedef struct nha_tro
{
    char name[5];
    float area;
    int dh;
}nha_tro;

int check_name(char s[])
{
    int len = strlen(s);
    if (len > 4 || len == 1) return 0;
    for(int i=0; i<len; i++)
    {
        if( ('a' > s[i] && s[i] > 'z') || ('A' > s[i] && s[i] > 'Z')) return 0;
    }
    return 1;
}

int input(nha_tro a[], int n, int sw1)
{
    printf("\n===== NHAP THONG TIN =====\n");
    int m, b;
    if(sw1 == 0)
    {
        printf("\nNhap so luong phong tro: "); scanf("%d", &n);
        for(int i=0; i<n; i++)
        {
            printf("Phong tro thu %d\n", i+1);
            printf("Nhap ten phong tro: "); scanf("%s", &a[i].name);
            while(check_name(a[i].name) == 0)
            {
                printf("Ten phong khong hop le. Nhap lai: "); scanf("%s", &a[i].name);
            }
            printf("Nhap dien tich phong: "); scanf("%f", &a[i].area);
            printf("Co dieu hoa (1-Co ; 0-Khong): "); scanf("%d", &a[i].dh);
            printf("-----------------------------------\n");
        }
    }
    else
    {
        printf("\nNhap so luong phong tro muon them: "); scanf("%d", &m);
        for(int i=n; i< (n+m); i++)
        {
            printf("Phong tro thu %d\n", i+1);
            printf("Nhap ten phong tro: "); scanf("%s", &a[i].name);
            printf("Nhap dien tich phong: "); scanf("%f", &a[i].area);
            printf("Co dieu hoa (1-Co ; 0-Khong): "); scanf("%d", &a[i].dh);
            printf("-----------------------------------\n");
        }
        n += m;
    }
    return n;
}


void output(nha_tro a[], int n)
{
    // printf("\n%d", n);
    printf("\n===== IN THONG TIN PHONG TRO =====\n");
    printf("\n%-20s%-20s%-20s", "Ten phong", "Dien tich", "Dieu hoa");
    printf("\n================================================");
    for(int i=0; i<n; i++)
    {
        printf("\n%-20s%-20.2f", a[i].name, a[i].area);
        if(a[i].dh == 1) printf("%-20s", "Co");
        else printf("%-20s", "Khong");
        printf("\n--------------------------------------------------");
    }
}

void search(nha_tro a[], int n)
{
    printf("\n===== TIM KIEM THEO DIEN TICH =====\n");
    float area;
    int sw = 0;
    printf("\nNhap dien tich muon tim: "); scanf("%f", &area);
    printf("\n%-20s%-20s%-20s", "Ten phong", "Dien tich", "Dieu hoa");
    printf("\n================================================");
    for(int i=0; i<n; i++)
    {

        if(abs(a[i].area - area) <= 5)
        {
            printf("\n%-20s%-20.2f", a[i].name, a[i].area);
            if(a[i].dh == 1) printf("%-20s", "Co");
            else printf("%-20s", "Khong");
            printf("\n--------------------------------------------------");
            sw++;
        }
    }
    if(sw == 0)
    {
        printf("\nKhong tim thay phong tro thoa man");
    }
}

void sort(nha_tro a[], int n)
{
    printf("\n===== SAP XEP THEO DIEN TICH =====\n");
    nha_tro tmp, a1[n];
    for(int i=0; i<n; i++) a1[i] = a[i];
    printf("\n%-20s%-20s%-20s", "Ten phong", "Dien tich", "Dieu hoa");
    printf("\n================================================");
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n ;j++)
        {
            if(a1[j].area > a1[i].area)
            {
                tmp = a1[i];
                a1[i] = a1[j];
                a1[j] = tmp;
            }
        }
    }
    for(int i=0; i<n; i++)
    {
        printf("\n%-20s%-20.2f", a1[i].name, a1[i].area);
        if(a1[i].dh == 1) printf("%-20s", "Co");
        else printf("%-20s", "Khong");
        printf("\n--------------------------------------------------");
    }
}

void analyze(nha_tro a[], int n)
{
    printf("\n===== SO LUONG DIEU HOA CAN THEM =====\n");
    int DH[4];
    for(int i=0; i<4; i++) DH[i] = 0;
    for(int i=0; i<n; i++)
    {
        if(a[i].dh == 0)
        {
            if(a[i].area <15) DH[0]++;
            if(a[i].area >= 15 && a[i].area < 22) DH[1]++;
            if(a[i].area >= 22 && a[i].area < 30) DH[2]++;
            if(a[i].area >= 30 && a[i].area < 40) DH[3]++;
        }
    }
    printf("\n%-20s%-20s", "Loai dieu hoa", "So luong");
    printf("\n======================================");
    printf("\n%-20s%-20d", "9000BTU", DH[0]);
    printf("\n--------------------------------------");
    printf("\n%-20s%-20d", "12000BTU", DH[1]);
    printf("\n--------------------------------------");
    printf("\n%-20s%-20d", "18000BTU", DH[2]);
    printf("\n--------------------------------------");
    printf("\n%-20s%-20d", "21000BTU", DH[3]);
    printf("\n--------------------------------------");
}

int main()
{
    nha_tro array[100];
    int sw, n = 0, sw1 = 0;
    while(1)
    {
        printf("\n\nFunctions");
        printf("\n1. Nhap thong tin phong tro.");
        printf("\n2. In thong tin phong tro");
        printf("\n3. Tim kiem theo dien tich");
        printf("\n4. Sap xep theo dien tich");
        printf("\n5. Thong ke dieu hoa");
        printf("\n6. Exit");
        printf("\n==============================");
        printf("\nEnter: "); scanf("%d", &sw);

        switch(sw)
        {
            case 1: n = input(array, n, sw1); sw1 = 1; break;
            case 2: output(array, n); break;
            case 3: search(array, n); break;
            case 4: sort(array, n); break;
            case 5: analyze(array, n); break;
            case 6: printf("\n>>>> End Program <<<<\n\n"); return 0;
        }
    }
    return 0;
}
