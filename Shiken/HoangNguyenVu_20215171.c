#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct kien_hang
{
    char ma_kh[21];
    float L, W, H;
    float KL, KL_TP;
    int kieuVC;
    char ma_loi[4];
    double phi;
}kien_hang;

int check_ma(char s[])
{
    int len = strlen(s);
    if (len<8 || len>20) return 0;
    else
    {
        for(int i=0; i<len; i++)
        {
            if (!(('a' <= (s[i]) && (s[i]) <= 'z') || ('A' <= (s[i]) && (s[i]) <= 'Z') || ('0' <= (s[i]) && (s[i]) <= '9'))) return 0;
        }
        return 1;
    }  
}

int check_loi(float L, float W, float H, float KL)
{
    if( L < 10 || W < 10 || H < 10 ) return 1;
    if( (L + W + H) > 150) return 2;
    if(KL > 30) return 3;
    return 0;
}

float trong_luong_tinh_phi(float L, float W, float H, float KL, int vc)
{
    float t;
    if((L + W + H) < 80)   t = KL;
    else
    {
        if (vc == 0)   t = (L * W * H)/6000;
        else    t = (L * W * H)/4000;
    }
    return t;
}

double tinh_phi(float KL_TP, int vc)
{
    double phi;
    if (KL_TP <= 3)   
    {
        if (vc == 0)    phi = 16500;
        else    phi = 22000;
    }
    else
    {
        if (vc == 0)    phi = 16500 + ((KL_TP-3)/0.5)*2500;
        else    phi = 22000 + ((KL_TP-3)/0.5)*2500;
    }
    return phi;
}

int function1(kien_hang mang[])
{
    int n, m;
    printf("\n===== Nhap thong tin =====");
    printf("\nNhap so kien hang: "); scanf("%d", &n);
    while(n<1 || n>100)
    {
        printf("\nSo luong khong hop le. Nhap lai: "); scanf("%d", &n);
    }
    for(int i=0; i<n; i++)
    {
        printf("\nKien hang thu %d", i+1);
        printf("\nMa kien hang: "); scanf("%s", &mang[i].ma_kh);
        while(1)
        {
            if(check_ma(mang[i].ma_kh) == 1) break;
            else
            {
                printf("Ma kien hang khong hop le. Nhap lai: "); scanf("%s", &mang[i].ma_kh);
            }
        }  
        printf("Chieu dai (cm): "); scanf("%f", &mang[i].L);
        printf("Chieu rong (cm): "); scanf("%f", &mang[i].W);
        printf("Chieu cao (cm): "); scanf("%f", &mang[i].H);
        printf("Trong luong tinh (kg): "); scanf("%f", &mang[i].KL);
        int c = check_loi(mang[i].L, mang[i].W, mang[i].H, mang[i].KL);
        switch (c)
        {
            case 0: strcpy(mang[i].ma_loi, "Ko"); break;
            case 1: strcpy(mang[i].ma_loi, "ER1"); break;
            case 2: strcpy(mang[i].ma_loi, "ER2"); break;
            case 3: strcpy(mang[i].ma_loi, "ER3"); break;
        }
        // printf("\n%s", mang[i].ma_loi);
        printf("Loai van chuyen (1-van chuyen nhanh ; 0-van chuyen thuong): "); scanf("%d", &mang[i].kieuVC);
        while(mang[i].kieuVC != 0 && mang[i].kieuVC != 1)
        {
            printf("Loai van chuyen khong hop le. Nhap lai: "); scanf("%d", &mang[i].kieuVC);
        }
        mang[i].KL_TP = trong_luong_tinh_phi(mang[i].L, mang[i].W, mang[i].H, mang[i].KL, mang[i].kieuVC);
        mang[i].phi = tinh_phi(mang[i].KL_TP, mang[i].kieuVC);
        printf("----------------------------------------------------------------\n");
    }
    return n;
}

void function2(kien_hang mang[], int n)
{
    printf("\n===== CAC KIEN HANG BI TU CHOI =====");
    printf("\n%-20s%-20s", "Ma kien", "Li do tu choi");
    printf("\n-----------------------------------------");
    for(int i = 0; i < n; i++)
    {
        if(strcmp(mang[i].ma_loi, "Ko") != 0)
        {
            printf("\n%-20s%-20s", mang[i].ma_kh, mang[i].ma_loi);
        }
    }
}

int function3(kien_hang mang[], int n)
{
    int dem = 0;
    printf("\n===== CAC KIEN HANG HOP LE =====");
    printf("\n%-20s%-20s%-30s%-20s", "Ma kien", "Can nang tinh phi", "Hinh thuc van chuyen", "Cuoc phi");
    printf("\n----------------------------------------------------------------------------------------");
    for(int i=0; i< n; i++)
    {
        if(strcmp(mang[i].ma_loi, "Ko") == 0)
        {
            printf("\n%-20s%-20.2f", mang[i].ma_kh, mang[i].KL_TP);
            if(mang[i].kieuVC == 0)
            {
                printf("%-30s%-20.0f", "Van chuyen thuong", mang[i].phi);
            }
            else
            {
                printf("%-30s%-20.0f", "Van chuyen nhanh", mang[i].phi);
            }
            dem++;
        }
    }
    return dem;
}

void function4(kien_hang mang[], int n, int dem)
{
    double tong = 0;
    printf("\n===== TONG CHI PHI =====");
    printf("\nSo luong kien hang da nhan: %d", dem);
    for(int i=0; i< n; i++)
    {
        if(strcmp(mang[i].ma_loi, "Ko") == 0) tong += mang[i].phi;
    }
    printf("\nTong tien cuoc: %.0lf", tong);
    printf("\nVAT: %.0lf", tong*0.08);
    printf("\nTong chi phi: %.0lf", tong*1.08);
}


void main()
{
    kien_hang array[100];
    int sw, sw1 = 0, n, dem;
    while (1)
    {
        printf("\n\nFunctions\n");
        printf("===================\n");
        printf("1. Nhap thong tin kien hang\n");
        printf("2. In cac kien hang bi tu choi\n");
        printf("3. In cac kien hang hop le\n");
        printf("4. Tinh phi van chuyen\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &sw);
        switch (sw)
        {
            case 1: n = function1(array); break;
            case 2: function2(array, n); break;
            case 3: dem = function3(array, n); break;
            case 4: function4(array, n, dem); break;
            case 5: printf("\n>>>>> End Program <<<<<\n\n"); return;
        }
    }
}
