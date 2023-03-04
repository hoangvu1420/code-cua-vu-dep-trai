#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define N 256

typedef struct cauhoi
{
    int nhom;
    char noidung[225];
    char dapan[5][225];
}cauhoi;

int ds_nhom[100];// Mảng các nhóm 
int so_nhom = 0;// Biến đếm số nhóm

void kt_nhom(int num)// Hàm kiểm tra xem nhóm đã tồn tại chưa
{
    for(int i = 0; i < so_nhom; i++)
    {
        if (ds_nhom[i] == num) return;// Nếu nhóm đã tồn tại trước đó thì kết thúc hàm
    }
    ds_nhom[so_nhom] = num;// không thì gán nhóm mới vào mảng các nhóm và tăng số nhóm
    so_nhom++;
}

int check_random(int chosen[], int current, int ran)// Hàm check xem số được random đã xuất hiện chưa
{
    for(int i = 0; i < current; i++)
    {
        if(chosen[i] == ran) return 0;// Nếu đã xuất hiện thì trả về 0 ngược lại trả về 1
    }
    return 1;
}

int GetRandom(int min,int max)// Hàm lấy random các số từ min đến max
{
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main()
{
    cauhoi array[100];
    FILE *fpt;
    int num = -1, stt_dapAn = 0;
    char c1,c2,s[100];
    fpt = fopen("C:\\Users\\FPTSHOP\\OneDrive - Hanoi University of Science and Technology\\Desktop\\cauhoi.txt","r");// Mở file ngân hàng
    if(fpt == NULL)// Check file
    {
        printf("ERROR: Failed to open");
    }
    fseek(fpt, SEEK_SET, 0);
    while(1)
    {
        c1 = fgetc(fpt);// Quét tất cả các kí tự trong file
        if(c1 == EOF) break;
        else if(c1 == '*')// Nếu gặp kí tự ‘*’
        {
            num++;// tăng số câu lên 
            fscanf(fpt, "*%d", &array[num].nhom);// Quét lấy nhóm của câu hỏi
            kt_nhom(array[num].nhom);// Kiểm tra xem nhóm đã được cho vào mảng nhóm chưa
            fscanf(fpt, " %[^\n]s", &array[num].noidung);// Quét lấy nội dung câu hỏi
            stt_dapAn = 0;// đặt số thứ tự đáp án bằng 0
        }
        else if (c1 == '#')// nếu gặp kí tự ‘#’
        {
            fscanf(fpt," %[^\n]s",array[num].dapan[stt_dapAn]);//quét lấy nội dung của đáp án
            stt_dapAn++;// tăng số thứ tự đáp án lên
        }
    }
    printf("\nTotal number: %d\n",num+1);
    printf("Number of chap: %d\n",so_nhom);
    cauhoi tmp;//tạo biến trung gian để sắp xếp các câu hỏi theo thứ tự nhóm từ bé đến lớn
    for(int i=0; i<num; i++)
    {
        for(int j=i+1; j<=num; j++)
        {
            if(array[i].nhom > array[j].nhom)
            {
                tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
        }
    }
// in ra các câu hỏi và đáp án
    for (int i = 0; i <= num; i++)
    {
        int j = 0;
        printf("\n<%d> %s",array[i].nhom,array[i].noidung);
        while(strcmp(array[i].dapan[j],"") != 0)// kiểm tra nếu đáp án khác rỗng
        {
            printf("\n%c, %s",'a'+j,array[i].dapan[j]);
            j++;
        }
    }
    int chosen[10];// tạo mảng các số được random
    srand((unsigned int)time(NULL));// hàm random theo thời gian thực
    int i;
    while(i < 10)
    {
        int r = GetRandom(1,num);
        if(check_random(chosen, i+1, r))// check xem số được random đã xuất hiện chưa
        {
            chosen[i] = r;
            printf("%d\n", r);
            i++;
        }
    }
    FILE *fot = fopen("C:\\Users\\FPTSHOP\\OneDrive - Hanoi University of Science and Technology\\Desktop\\dethi.txt","w");// mở file đề thi
    if(fot == NULL) printf("\nERROR opening file");
    else
    {
        printf("\n================================");
        printf("\nDe Thi\n");
        fprintf(fot, "De Thi 10 cau ngau nhien\n");
        fprintf(fot, "================================\n");
        for (int i = 0; i < 10; i++)
        {
// in 10 câu hỏi trong mảng cauhoi với số thứ tự là các phần tử trong mảng chosen
            printf("\nQ%d. %s", i+1, array[chosen[i]].noidung);
            fprintf(fot,"\nQ%d. %s", i+1, array[chosen[i]].noidung);
            for(int j=0; j < 5; j++)
            {
                strcpy(s,array[chosen[i]].dapan[j]);
                if(strcmp(s,"") != 0)
                {
                    printf("\n%c, %s", 'a'+j, s);
                    fprintf(fot,"\n%c, %s", 'a'+j, s);
                }
            }
            fprintf(fot, "\n--------------");
        }
        printf("\n================================");
    }
    fclose(fot);
    fclose(fpt);// đóng các file
    return 0;
}
