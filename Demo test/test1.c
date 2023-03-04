#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct vdv
{
    int id;
    char nation[4];
    char name[30];
    float R[3], FR;
} vdv;

int input(vdv mang[])
{
    int n;
    printf("\n===NHAP VDV THAM GIA THI DAU===");
    printf("\nNhap so luong vdv: "); scanf("%d", &n);
    while (n<0 || n>20)
    {
        printf("\nSo luong khong hop le. Nhap lai: "); scanf("%d",&n);
    }
    
    for(int i=0; i<n; i++)
    {
        printf("\nVDV thu %d\n",i+1);
        printf("%-10s","ID");scanf("%d",&mang[i].id);
        printf("%-10s","Nation"); scanf("%s",&mang[i].nation); fflush(stdin);
        printf("%-10s","Name"); scanf("%[^\n]s", mang[i].name);
        // printf("%-10s","Name"); fgets(mang[i].name, sizeof(mang[i].name), stdin);//
        printf("----------------------------------------");
    }
    printf("\nNhap hoan tat");
    return n;
}

void output(vdv mang[], int n)
{
    printf("\n===IN THONG THIN===");
    printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
    for(int j=0; j<76; j++) printf("="); 
    printf("\n");
    for(int i=0; i<n; i++)
    {
        printf("\n%-5d%-10s%-20s\n", mang[i].id, mang[i].nation, mang[i].name);
        for(int j=0; j<76; j++) printf("-");
    }
}

void thi_dau(vdv mang[], int n)
{
    printf("\n===NHAP KET QUA THI DAU===");
//
    printf("\n\tRound 1\n");
    for(int i=0; i<n; i++)
    {
        printf("%-5d%-10s%-20sDiem R1: ", mang[i].id, mang[i].nation, mang[i].name); scanf("%f", &mang[i].R[0]);
        while (mang[i].R[0] < 0 || mang[i].R[0] > 20)
        {
            printf("Diem khong shop le. Nhap lai: "); scanf("%f", &mang[i].R[0]);
        }
    }
    
    printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
    for(int j=0; j<76; j++) printf("=");
    for(int i=0; i<n; i++)
    {
        printf("\n%-5d%-10s%-20s%-10.2f\n", mang[i].id, mang[i].nation, mang[i].name, mang[i].R[0]);
        for(int j=0; j<76; j++) printf("-");
    }
//
    printf("\n\n\tRound 2\n");
    for(int i=0; i<n; i++)
    {
        printf("%-5d%-10s%-20sDiem R2: ", mang[i].id, mang[i].nation, mang[i].name); scanf("%f", &mang[i].R[1]);
        while (mang[i].R[1] < 0 || mang[i].R[1] > 20)
        {
            printf("Diem khong shop le. Nhap lai: "); scanf("%f", &mang[i].R[1]);
        }
    }
    printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
    for(int j=0; j<76; j++) printf("=");
    for(int i=0; i<n; i++)
    {
        printf("\n%-5d%-10s%-20s%-10.2f%-10.2f\n", mang[i].id, mang[i].nation, mang[i].name, mang[i].R[0], mang[i].R[1]);
        for(int j=0; j<76; j++) printf("-");
    }
//
    printf("\n\n\tRound 3\n");
    for(int i=0; i<n; i++)
    {
        printf("%-5d%-10s%-20sDiem R3: ", mang[i].id, mang[i].nation, mang[i].name); scanf("%f", &mang[i].R[2]);
        while (mang[i].R[2] < 0 || mang[i].R[2] > 20)
        {
            printf("Diem khong shop le. Nhap lai: "); scanf("%f", &mang[i].R[2]);
        }
    }
    printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
    for(int j=0; j<76; j++) printf("=");
    for(int i=0; i<n; i++)
    {
        float max = 0;
        for(int j=0; j<3; j++)
        {
            if (mang[i].R[j] > max) max = mang[i].R[j];
        }
        mang[i].FR = max;
        printf("\n%-5d%-10s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", mang[i].id, mang[i].nation, mang[i].name, mang[i].R[0], mang[i].R[1], mang[i].R[2], mang[i].FR);
        for(int j=0; j<76; j++) printf("-");
    }
    printf("\nKet thuc nhap");
}

void search(vdv mang[], int n)
{
    int sw, m;
    printf("\n===TIM KIEM====");
    while(1)
    {
        printf("\n\nMenu tim kiem");
        printf("\n1-Tim kiem theo quoc gia");
        printf("\n2-Tim kiem theo ten");
        printf("\n3-Thoat");
        printf("\nNhap function: "); scanf("%d",&sw);

        switch(sw)
        {
            case 1: 
            {
                char s[4];
                printf("\nNhap quoc gia muon tim kiem: ");scanf("%s",&s);
                printf("\tKet qua");
                printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
                for(int j=0; j<76; j++) printf("=");
                for(int i=0; i<n; i++)
                {
                    if(strcmp(mang[i].nation, s) == 0)
                    {
                        printf("\n%-5d%-10s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", mang[i].id, mang[i].nation, 
                        mang[i].name, mang[i].R[0], mang[i].R[1], mang[i].R[2], mang[i].FR);
                        for(int j=0; j<76; j++) printf("-");
                    }
                }
                break;
            }    
            case 2:
            {
                char s[30], *cmp;
                printf("\nNhap ten muon tim: "); scanf("%s", &s);
                printf("\tKet qua");
                printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
                for(int j=0; j<76; j++) printf("=");
                for(int i=0; i<n; i++)
                {
                    cmp = strstr(mang[i].name, s);
                    if(cmp != NULL)
                    {
                        printf("\n%-5d%-10s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", mang[i].id, mang[i].nation, 
                        mang[i].name, mang[i].R[0], mang[i].R[1], mang[i].R[2], mang[i].FR);
                        for(int j=0; j<76; j++) printf("-");
                    }
                }
                break;
            } 
            case 3: printf("\nKet thuc"); m=1; break;
        }
        if(m == 1) break;
    }
}

void swap(vdv *vdv1, vdv *vdv2)
{
    vdv tmp;
    tmp = *vdv1;
    *vdv1 = *vdv2;
    *vdv2 = tmp;
}
void ket_qua(vdv mang[], int n)
{

    printf("\n===KET QUA===\n");
    
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(mang[j].FR > mang[i].FR) swap(&mang[i], &mang[j]);
        }
    }
    printf("\n%-5s%-10s%-20s%-10s%-10s%-10s%-10s\n","ID","Nation","Name","R1","R2","R3","FR");
    for(int j=0; j<76; j++) printf("=");
    for(int i=0; i<n; i++)
    {
        printf("\n%-5d%-10s%-20s%-10.2f%-10.2f%-10.2f%-10.2f\n", mang[i].id, mang[i].nation, 
        mang[i].name, mang[i].R[0], mang[i].R[1], mang[i].R[2], mang[i].FR);
        for(int j=0; j<76; j++) printf("-");
    }
}

void main()
{
    vdv arr[21];
    int sw1 = 0, sw3 = 0, n, f, ct;
    while (1)
    {
        printf("\n\nMenu functions\n");
        printf("1-Nhap thong tin truoc khi thi dau\n");
        printf("2-In thong tin\n");
        printf("3-Nhap ket qua thi dau\n");
        printf("4-Tim kiem\n");
        printf("5-In ket qua\n");
        printf("6-Thoat chuong trinh\n");
        printf("Nhap function: ");
        scanf("%d", &f);

        switch (f)
        {
        case 1:
        {
            if (sw1 == 1)
            {
                printf("\nChuc nang nay chi co the thuc hien 1 lan\n");
                break;
            }
            else
            {
                n = input(arr);
                sw1 = 1;
                break;
            }
        }
        case 2:
        {
            if (sw1 == 0)
            {
                printf("\nCan nhap thong tin truoc\n");
                break;
            }
            else
            {
                output(arr, n);
                break;
            }
        }
        case 3:
        {
            if (sw1 == 0)
            {
                printf("\nCan nhap thong tin truoc\n");
                break;
            }
            else
            {
                if (sw3 == 1)
                {
                    printf("\nChuc nang nay chi co the thuc hien 1 lan\n");
                    break;
                }
                else
                {
                    thi_dau(arr, n); sw3 = 1; break;
                }
            }
        }
        case 4:
        {
            if (sw1 == 0 || sw3 == 0)
            {
                printf("\nCan nhap thong tin truoc\n");
                break;
            }
            else
            {
                search(arr, n);
                break;
            }
        }
        case 5:
        {
            if (sw1 == 0 || sw3 == 0)
            {
                printf("\nCan nhap thong tin truoc\n");
                break;
            }
            else
            {
                ket_qua(arr, n);
                break;
            }
        }
        case 6:
            printf("\n>>>>>> End Program <<<<<<<\n");
            ct = 1;
            break;
        }
        if (ct == 1)
            break;
    }
}
