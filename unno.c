#include<stdio.h>
#include<string.h>

typedef struct SV
{
    char name[100];
    char lop[10];
    int tuoi;
    float diem[7];
    float TB;
}SV;

int input(SV a[])
{
    int n = 0;
    // char c;
    FILE *f = fopen("unno.txt", "r");
    if(feof(f)) printf("\nError");
    else
    {
        fseek(f, SEEK_SET, 0);
        while(1)
        {
            char c = fgetc(f);
            if(c == EOF) break;
            else if(c == '\n') 
            {
                fscanf(f, "%[^;]", &a[n].name);
                fscanf(f, ";%[^;]", &a[n].lop);
                fscanf(f, ";%d;", &a[n].tuoi);
                fscanf(f, "%f;%f;%f;%f;%f;%f", &a[n].diem[0], &a[n].diem[1], &a[n].diem[2], &a[n].diem[3], &a[n].diem[4], &a[n].diem[5]);
                n++;
            }
        }
    }
    fclose(f);
    return n;
}

void output(SV a[], int n)
{
    printf("\n                                        ===== BẢNG THÔNG TIN SINH VIÊN =====");
    printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
    printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
    "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
    printf("|");
    for(int i = 0; i < n; i++)
    {
        printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
        printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
        float sum = 0;
        for(int j = 0; j < 6; j++) 
        {
            printf("| %-8.1f", a[i].diem[j]);
            sum += a[i].diem[j];
        }
        a[i].TB = sum/6;
        printf("| %-8.2f", a[i].TB);
        printf("|");
    }
    printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
    printf("\n");
}

float check_point(float *x)
{
    while (*x < 0 || *x > 10.0) 
    {
        printf("Điểm không hợp lệ, nhập lại: ");
        scanf("%f", &*x);
    }
    return *x;
}

void themSV(SV a[], int *n)
{
    int x;
    printf("\n===== THÊM SINH VIÊN =====");
    printf("\nNhập số sinh viên muốn thêm: "); scanf("%d", &x);
    for(int i=0; i<x; i++)
    {
        printf("\nSinh viên thứ %d\n", i+1);
        fflush(stdin);
        printf("Tên: "); scanf("%[^\n]", &a[*n+i].name);
        printf("Lớp: "); scanf("%s", &a[*n+i].lop);
        printf("Tuổi: "); scanf("%d", &a[*n+i].tuoi);
        printf("Điểm: ");
        printf("\nToán: "); scanf("%f", &a[*n+i].diem[0]);
        check_point(&a[*n+i].diem[0]);
        printf("Văn: "); scanf("%f", &a[*n+i].diem[1]);
        check_point(&a[*n+i].diem[1]);
        printf("Anh: "); scanf("%f", &a[*n+i].diem[2]);
        check_point(&a[*n+i].diem[2]);
        printf("Lý: "); scanf("%f", &a[*n+i].diem[3]);
        check_point(&a[*n+i].diem[3]);
        printf("Hoá: "); scanf("%f", &a[*n+i].diem[4]);
        check_point(&a[*n+i].diem[4]);
        printf("Sinh: "); scanf("%f", &a[*n+i].diem[5]);
        check_point(&a[*n+i].diem[5]);
    }
    *n += x;
    printf("\n----- Hoàn tất thêm %d sinh viên -----\n", x);
}

void sua_tt(SV a[], int n)
{
    int x;
    printf("\n===== SỬA THÔNG TIN SINH VIÊN =====");
    printf("\nNhập stt sinh viên muốn sửa: "); scanf("%d", &x);
    printf("\nNhập thông tin sửa đổi");
    fflush(stdin);
    printf("\nTên: "); scanf("%[^\n]", &a[x-1].name);
    printf("Lớp: "); scanf("%s", &a[x-1].lop);
    printf("Tuổi: "); scanf("%d", &a[x-1].tuoi);
    printf("Điểm: ");
    printf("\nToán: "); scanf("%f", &a[x-1].diem[0]);
        check_point(&a[x-1].diem[0]);
    printf("Văn: "); scanf("%f", &a[x-1].diem[1]);
        check_point(&a[x-1].diem[1]);
    printf("Anh: "); scanf("%f", &a[x-1].diem[2]);
        check_point(&a[x-1].diem[2]);
    printf("Lý: "); scanf("%f", &a[x-1].diem[3]);
        check_point(&a[x-1].diem[3]);
    printf("Hoá: "); scanf("%f", &a[x-1].diem[4]);
        check_point(&a[x-1].diem[4]);
    printf("Sinh: "); scanf("%f", &a[x-1].diem[5]);
        check_point(&a[x-1].diem[5]);
    printf("\n----- Hoàn tất sửa thông tin sinh viên -----", x);
    printf("\n");
}

void xoa_SV(SV a[], int *n)
{
    int x;
    printf("\n===== XOÁ SINH VIÊN =====");
    printf("\nNhập stt sinh viên muốn xoá: "); scanf("%d", &x);
    *n -= 1;
    for(int i=x; i<*n; i++)
    {
        a[i] = a[i+1];
    }
    printf("\n----- Hoàn tất xoá thông tin sinh viên -----\n");
}

void search(SV a[], int n)
{
    int sw, s3;
    char s1[50], s2[10];
    printf("\n===== TÌM KIẾM SINH VIÊN =====");
    while(1)
    {
        printf("\n1 - Tìm kiếm theo tên");
        printf("\n2 - Tìm kiếm theo lớp");
        printf("\n3 - Tìm kiếm theo tuổi");
        printf("\n4 - Thoát");
        printf("\nNhập tuỳ chọn: "); scanf("%d", &sw);
        switch (sw)
        {
            case 1: 
            {
                printf("\nNhập tên sinh viên muốn tìm: "); scanf("%s", s1);
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    char *cmp = strstr(a[i].name, s1);
                    if(cmp != NULL)
                    {
                        printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                        printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                        for(int j = 0; j < 6; j++) printf("| %-8.1f", a[i].diem[j]);
                        printf("| %-8.2f", a[i].TB);
                        printf("|");
                    } 
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            }; break;
            case 2:
            {
                printf("\nNhập lớp muốn tìm: "); scanf("%s", &s2);
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    if(strcmp(a[i].lop, s2) == 0)
                    {
                        printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                        printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                        for(int j = 0; j < 6; j++) printf("| %-8.1f", a[i].diem[j]);
                        printf("| %-8.2f", a[i].TB);
                        printf("|");
                    } 
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            } break;
            case 3:
            {
                printf("\nNhập tuổi muốn tìm: "); scanf("%d", &s3);
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    if(a[i].tuoi == s3)
                    {
                        printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                        printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                        for(int j = 0; j < 6; j++) printf("| %-8.1f", a[i].diem[j]);
                        printf("| %-8.2f", a[i].TB);
                        printf("|");
                    } 
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            }; break;
            case 4: printf("\n----- Hoàn tất -----\n"); return;
        }
    }
}

void swap(SV *a, SV *b)
{
    SV tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void sap_xep(SV b[], int n)
{
    int sw;
    SV a[100];
    for (int i = 0; i < n; i++) a[i] = b[i];
    while(1)
    {
        printf("\n===== SẮP XẾP THEO YÊU CẦU =====");
        printf("\n1 - Sắp xếp theo tên");
        printf("\n2 - Sắp xếp theo điểm TB");
        printf("\n3 - Sắp xếp theo tuổi");
        printf("\n4 - Thoát");
        printf("\nNhập tuỳ chọn: "); scanf("%d", &sw);
        switch(sw)
        {
            case 1:
            {
                for (int i = 0; i < n; i++) 
                    for (int j = i+1; j < n; j++) 
                    {
                        if(strcmp(a[i].name, a[j].name) > 0)
                        {
                            swap(&a[i], &a[j]);
                        }
                    }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                    printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                    for(int j = 0; j < 6; j++) 
                    {
                        printf("| %-8.1f", a[i].diem[j]);
                    }
                    printf("| %-8.2f", a[i].TB);
                    printf("|");
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            }; break;
            case 2:
            {
                for(int i = 0; i < n; i++)
                    for(int j = i+1; j < n; j++)
                    {
                        if(a[i].TB < a[j].TB)
                        {
                            swap(&a[i], &a[j]);
                        }
                    }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                    printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                    for(int j = 0; j < 6; j++) 
                    {
                        printf("| %-8.1f", a[i].diem[j]);
                    }
                    printf("| %-8.2f", a[i].TB);
                    printf("|");
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            }; break;
            case 3:
            {
                for(int i = 0; i < n; i++)
                    for(int j = i+1; j < n; j++)
                    {
                        if(a[i].tuoi < a[j].tuoi)
                        {
                            swap(&a[i], &a[j]);
                        }
                    }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n%-6s%-23s%-12s%-12s%-11s%-11s%-10s%-11s%-11s%-10s%-13s","| STT","| Họ Tên","| Lớp","| Tuổi",
                "| Toán","| Văn","| Anh","| Lý","| Hóa","| Sinh","| Điểm TB");
                printf("|");
                for(int i=0; i<n; i++)
                {
                    printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                    printf("\n| %-4d| %-18s| %-8s| %-8d", i+1, a[i].name, a[i].lop, a[i].tuoi);
                    for(int j = 0; j < 6; j++) 
                    {
                        printf("| %-8.1f", a[i].diem[j]);
                    }
                    printf("| %-8.2f", a[i].TB);
                    printf("|");
                }
                printf("\n+-----+-------------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+");
                printf("\n");
            }; break;
            case 4: printf("\n----- Hoàn tất -----\n"); return;
        }
    }
}

void thong_ke(SV a[], int n)
{
    while(1)
    {
        int sw;
        printf("\n===== THỐNG KÊ DỮ LIỆU =====");
        printf("\n1 - Thống kê chung");
        printf("\n2 - Học lực");
        printf("\n3 - Thống kê các lớp");
        printf("\n4 - Thoát");
        printf("\nNhập tuỳ chọn: "); scanf("%d", &sw);
        switch(sw)
        {
            case 1:
            {
                float sum = 0, max = 0, min = 10, tb;
                int tmax = 0, tmin = 50;
                for(int i = 0; i<n; i++)
                {
                    sum += a[i].TB;
                    if(a[i].TB > max) max = a[i].TB;
                    if(a[i].TB < min) min = a[i].TB;
                    if(a[i].tuoi > tmax) tmax = a[i].tuoi;
                    if(a[i].tuoi < tmin) tmin = a[i].tuoi;
                }
                tb = sum / n;
                printf("\nĐiểm TB tất cả: %.2f", tb);
                printf("\nĐiểm TB lớn nhất: %.2f", max);
                printf("\nĐiểm TB thấp nhất: %.2f", min);
                printf("\nTuổi lớn nhất: %d", tmax);
                printf("\nTuổi thấp nhất: %d", tmin);
                printf("\n");
            }; break;
            case 2:
            {
                int g = 0, k = 0, tb = 0, y = 0;
                printf("\n%-23s%-12s%-18s", "| Họ Tên", "| Lớp", "| Học Lực");
                printf("\n---------------------------------------------");
                for(int i=0; i<n; i++)
                {
                    if(a[i].TB >= 8.0)
                    {
                        printf("\n| %-18s| %-8s| %-13s", a[i].name, a[i].lop, "Giỏi"); g++;
                        printf("\n---------------------------------------------");
                    }
                    if(a[i].TB < 8.0 && a[i].TB >= 6.5)
                    {
                        printf("\n| %-18s| %-8s| %-13s", a[i].name, a[i].lop, "Khá"); k++;
                        printf("\n---------------------------------------------");
                    }
                    if(a[i].TB < 6.5 && a[i].TB >= 5.0)
                    {
                        printf("\n| %-18s| %-8s| %-13s", a[i].name, a[i].lop, "Trung Bình"); tb++;
                        printf("\n---------------------------------------------");
                    }
                    if(a[i].TB < 5.0)
                    {
                        printf("\n| %-18s| %-8s| %-13s", a[i].name, a[i].lop, "Yếu"); y++;
                        printf("\n---------------------------------------------");
                    }
                }
                printf("\nTổng số sinh viên loại giỏi: %d (%.1f%%)", g, ((float)g/n)*100);
                printf("\nTổng số sinh viên loại khá: %d (%.1f%%)", k, ((float)k/n)*100);
                printf("\nTổng số sinh viên loại trung bình: %d (%.1f%%)", tb, ((float)tb/n)*100);
                printf("\nTổng số sinh viên loại yếu: %d (%.1f%%)", y, ((float)y/n)*100);
                printf("\n");
            }; break;
            case 3:
            {
                for(int i = 0; i < n; i++)
                {
                    int sw1 = 0;
                    for(int j=0; j<i; j++)
                    {
                        if(strcmp(a[i].lop, a[j].lop) == 0) sw1 = 1;
                    }
                    if(sw1 == 0)
                    {
                        printf("\n\tLớp %s", a[i].lop);
                        float max = 0, min = 10.0;
                        int dem = 0;
                        for(int j=0; j<n; j++)
                        {
                            if(strcmp(a[i].lop, a[j].lop) == 0) 
                            {
                                dem++;
                                if(a[j].TB < min) min = a[j].TB; 
                                if(a[j].TB > max) max = a[j].TB;
                            } 
                        }
                        printf("\nSố sinh viên: %d", dem);
                        printf("\nĐiểm TB cao nhất lớp: %.2f", max);
                        printf("\nĐiểm TB thấp nhất lớp: %.2f", min);
                        printf("\n---------------------------");
                    }
                }
                printf("\n");
            }; break;
            case 4: printf("\n----- Hoàn tất -----\n"); return;
        }
    }
}

void sao_luu(SV a[], int n)
{
    printf("\n===== SAO LƯU DỮ LIỆU =====");
    int i = 0;
    FILE *fot = fopen("unno.txt", "w");
    if(fot == NULL) printf("\nError");
    else
    {
        fseek(fot, SEEK_SET, 0);
        fprintf(fot, "Danh sach SV\n");
        while(i < n)
        {
            fprintf(fot, "%s;%s;%d;%.1f;%.1f;%.1f;%.1f;%.1f;%.1f", a[i].name, a[i].lop, a[i].tuoi, 
            a[i].diem[0], a[i].diem[1], a[i].diem[2], a[i].diem[3], a[i].diem[4], a[i].diem[5]);
            if(i != (n-1)) fprintf(fot, "\n"); 
            i++;
        }
        printf("\n----- Sao lưu hoàn tất -----");
        printf("\n");
    }
    fclose(fot);
}

void main()
{
    int sw, n;
    SV a[100];
    n = input(a);
    while(1)
    {
        printf("\n******** MENU ********");
        printf("\n1 - In danh sách SV");
        printf("\n2 - Thêm SV");
        printf("\n3 - Sửa thông tin SV");
        printf("\n4 - Xóa SV");
        printf("\n5 - Tìm kiếm");
        printf("\n6 - Sắp xếp");
        printf("\n7 - Thống kê");
        printf("\n8 - Sao lưu dữ liệu");
        printf("\n**********************");
        printf("\nEnter your choice: "); scanf("%d", &sw);
        switch(sw)
        {
            case 1: output(a, n); break;
            case 2: themSV(a, &n); break;
            case 3: sua_tt(a, n); break;
            case 4: xoa_SV(a, &n); break;
            case 5: search(a, n); break;
            case 6: sap_xep(a, n); break;
            case 7: thong_ke(a, n); break;
            case 8: sao_luu(a, n); break;
        }
    }
}
