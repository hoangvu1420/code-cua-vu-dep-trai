#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct day
{
    int year, month, day;
}day;

typedef struct transaction
{
    day trans_day;
    int trans_type;
    double trans_amount;
    double current_balance;
}trans;

typedef struct customer
{
    char soTK[11];
    char MK[7];
    day ngay_taoTK;
    char ten_chuTK[20];
    day ngay_sinh_chuTK;
    char cmnd[10];
    double soDu;
    int flag;
    trans BD_soDu[10];
    int soBD;
}cus;

typedef struct admin
{
    char tenTK[9];
    char mk[7];
    day ngay_taoTK;
    char tenAd[20];
}ad;

int input_cus(cus a[])
{
    int n = 0;
    FILE *f = fopen("banking.txt", "r");
    if(feof(f)) printf("\nERROR");
    else
    {
        fseek(f, 0, SEEK_SET);
        while(1)
        {
           char c = fgetc(f);
           if(c == EOF) break;
           else if(c == '=')
           {
                fscanf(f, "%[^|]", &a[n].soTK);
                fscanf(f, "|%[^|]", &a[n].MK);
                fscanf(f, "|%d/%d/%d", &a[n].ngay_taoTK.day, &a[n].ngay_taoTK.month, &a[n].ngay_taoTK.year);
                fscanf(f, "|%[^|]", &a[n].ten_chuTK);
                fscanf(f, "|%d/%d/%d", &a[n].ngay_sinh_chuTK.day, &a[n].ngay_sinh_chuTK.month, &a[n].ngay_sinh_chuTK.year);
                fscanf(f, "|%[^|]", &a[n].cmnd);
                fscanf(f, "|%d|", &a[n].flag);
                int n1 = 0;
                while(1)
                {
                    char c1 = fgetc(f);
                    if (c1 == '\n') break;
                    else if (c1 == '*')
                    {
                        fscanf(f, "%d/%d/%d-", &a[n].BD_soDu[n1].trans_day.day, &a[n].BD_soDu[n1].trans_day.month, &a[n].BD_soDu[n1].trans_day.year);
                        fscanf(f, "%d-", &a[n].BD_soDu[n1].trans_type);
                        fscanf(f, "%lf-", &a[n].BD_soDu[n1].trans_amount);
                        fscanf(f, "%lf-", &a[n].BD_soDu[n1].current_balance);

                        // printf("%d/%d/%d\n", a[n].BD_soDu[n1].trans_day.day, a[n].BD_soDu->trans_day.month, a[n].BD_soDu->trans_day.year);
                        n1++;
                    }
                }
                a[n].soDu = a[n].BD_soDu[n1-1].current_balance;
                a[n].soBD = n1;
                n++;
           }
        }
    }
    fclose(f);
    return n;
}

int input_ad(ad adm[])
{
    int n = 0;
    FILE *f = fopen("banking.txt", "r");
    if(feof(f)) printf("\nERROR");
    else
    {
        fseek(f, 0, SEEK_SET);
        while(1)
        {
           char c = fgetc(f);
           if(c == EOF) break;
           else if(c == '#')
           {
                fscanf(f, "%[^|]", &adm[n].tenTK);
                fscanf(f, "|%[^|]", &adm[n].mk);
                fscanf(f, "|%d/%d/%d", &adm[n].ngay_taoTK.day, &adm[n].ngay_taoTK.month, &adm[n].ngay_taoTK.year);
                fscanf(f, "|%[^\n]", &adm[n].tenAd);
                n++;
           }
           else if(c == '\n') continue;
        }
    }
    fclose(f);
    return n;
}

int login(cus a[], int n)
{
    char s[11], mk[7];
    printf("\n----Đăng nhập tài khoản----");
    printf("\nNhập số TK: "); scanf("%s", &s);
    fflush(stdin);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, s) == 0) x = i;
    }
    while(x == -1)
    {
        printf("Số TK không tồn tại, nhập lại: "); scanf("%s", &s);
        fflush(stdin);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, s) == 0) x = i;
        }
    }
    if(a[x].flag == 1) 
    {
        printf("\n");
        printf("----- Tài khoản đã bị khoá -----");
        return -1;
    }
    else
    {
        printf("Nhập mật khẩu: "); scanf("%s", &mk);
        int lan_nhap = 5;
        while(strcmp(mk, a[x].MK) != 0)
        {
            printf("Nhập sai mật khẩu, hãy nhập lại (còn %d lần nhập): ", lan_nhap); scanf("%s", &mk);
            lan_nhap--;
            if(lan_nhap == 0)
            {
                printf("Bạn đã nhập sai mật khẩu quá nhiều lần. Tài khoản của bạn sẽ bị khoá"); 
                a[x].flag = 1; 
                return -1;
            }
        }
    }
    printf("\n<<<Đăng nhập thành công>>>");
    printf("\nXin chào %s", a[x].ten_chuTK); 
    return x;
}

int GetRandom(int min,int max)// Hàm lấy random các số từ min đến max
{
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

day specify_today()
{
    day today;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    today.day = tm.tm_mday;
    today.month = tm.tm_mon + 1;
    today.year = tm.tm_year + 1900;
    return today;
}

void createAccount(cus a[], int *n)
{
    char news[11], mk[7];
    printf("\n-----Tạo tài khoản-----");
    srand((unsigned int)time(NULL));
    int sw, sw1 = 0;
    do
    {
        do
        {
            char s[8];
            strcpy(news, "110");
            sw1 = 0;
            int r = GetRandom(1000000, 9999999);
            itoa(r, s, 10);
            strcat(news, s);
            for(int i = 0; i<*n; i++)
            {
                if (strcmp(a[i].soTK, news) == 0) 
                {
                    sw1 = 1; printf("\nerror");
                }
            }
        }
        while(sw1 == 1);
        printf("\nSố tài khoản đề xuất: %s", news);
        printf("\n1 - Chấp nhận");
        printf("\n2 - Đổi số");
        printf("\n>>> ");
        scanf("%d", &sw);
    } while (sw == 2);
    strcpy(a[*n].soTK, news);
    printf("Nhập mật khẩu: "); scanf("%s", &a[*n].MK);
    while(strlen(a[*n].MK) != 6)
    {
        printf("Nhập lại mật khẩu: "); scanf("%s", &a[*n].MK);
    }
    fflush(stdin);
    printf("Nhập tên chủ TK: "); scanf("%[^\n]", &a[*n].ten_chuTK);
    a[*n].ngay_taoTK = specify_today();
    printf("Nhập ngày sinh (dd/mm/yyyy): "); scanf("%d/%d/%d",&a[*n].ngay_sinh_chuTK.day, &a[*n].ngay_sinh_chuTK.month, &a[*n].ngay_sinh_chuTK.year);
    printf("Nhập số CMND: "); scanf("%s", &a[*n].cmnd);
    a[*n].flag = 0;
    a[*n].BD_soDu[0].trans_day = specify_today();
    a[*n].BD_soDu[0].trans_type = 1;
    a[*n].BD_soDu[0].trans_amount = 50000;
    a[*n].BD_soDu[0].current_balance = 50000;
    a[*n].soDu = 50000;
    a[*n].soBD = 1;
    printf("\n>> Tạo tài khoản thành công <<");
    printf("\nSTK: %s", a[*n].soTK);
    printf("\nMK: %s", a[*n].MK);
    printf("\nNgày tạo tài khoản: %d/%d/%d", a[*n].ngay_taoTK.day, a[*n].ngay_taoTK.month, a[*n].ngay_taoTK.year);
    printf("\nTên chủ TK: %s", a[*n].ten_chuTK);
    printf("\nNgày sinh: %d/%d/%d", a[*n].ngay_sinh_chuTK.day, a[*n].ngay_sinh_chuTK.month, a[*n].ngay_sinh_chuTK.year);
    printf("\nSố CMND: %s", a[*n].cmnd);
    printf("\nSố dư: %.0lf", a[*n].soDu);
    printf("\n>> Hãy đăng nhập lại <<");
    *n += 1;
}

void transaction(cus a[], int n, int x)
{
    int sw, sw1 = 0;
    double t;
    printf("\n       -----Giao dịch-----");
    printf("\nNhập loại giao dịch (1-Gửi tiền;0-Rút tiền): "); scanf("%d", &sw);
    printf("Nhập số tiền giao dịch: "); scanf("%lf", &t);
    printf("\nXác nhận giao dịch");
    if(sw == 1) printf("\nLoại giao dịch: Gửi tiền");
    else printf("\nLoại giao dịch: Rút tiền");
    printf("\nSố tiền: %.0lf", t);
    printf("\n(1-Đồng ý; 0-Từ chối) "); scanf("%d", &sw1);
    if(sw1 == 1)
    {
        int y = a[x].soBD;
        a[x].BD_soDu[y].trans_day = specify_today();
        a[x].BD_soDu[y].trans_type = sw;
        a[x].BD_soDu[y].trans_amount = t;
        if(sw == 1) 
        {
            a[x].BD_soDu[y].current_balance = a[x].soDu + t;
            a[x].BD_soDu[y].trans_type = 1;
        }
        else 
        {
            if(a[x].soDu < t)
            {
                printf("\n>>> Giao dịch thất bại, số dư không đủ <<<");
                return;
            }
            a[x].BD_soDu[y].current_balance = a[x].soDu - t;
            a[x].BD_soDu[y].trans_type = 0;
        }
        a[x].soDu = a[x].BD_soDu[y].current_balance;
        a[x].soBD++;
        printf("\n>>> Giao dịch thành công <<<");
        printf("\nSố dư hiện tại: %.0lf", a[x].soDu);
        // printf("\nNgày: %d/%d/%d", a[x].BD_soDu[y].trans_day.day, a[x].BD_soDu[y].trans_day.month, a[x].BD_soDu[y].trans_day.year);
        // printf("\nSBĐ: %d", a[x].soBD);
    }
    else printf("\n>>> Huỷ giao dịch <<<");
}

void infor(cus a[], int n, int x)
{
    printf("\n-----Thông tin tài khoản-----");
    printf("\nSố tài khoản: %s", a[x].soTK);
    printf("\nMật khẩu: %s", a[x].MK);
    printf("\nNgày tạo tài khoản: %d/%d/%d", a[x].ngay_taoTK.day, a[x].ngay_taoTK.month, a[x].ngay_taoTK.year);
    printf("\nTên chủ TK: %s", a[x].ten_chuTK);
    printf("\nNgày sinh: %d/%d/%d", a[x].ngay_sinh_chuTK.day, a[x].ngay_sinh_chuTK.month, a[x].ngay_sinh_chuTK.year);
    printf("\nSố CMND: %s", a[x].cmnd);
}

void inforSettings(cus a[], int n, int x)
{
    int sw, d, m, y;
    char mk[7], name[20], cmnd[10];
    printf("\n-----Sửa đổi thông tin-----");
    printf("\nNhập thông tin muốn sửa");
    printf("\n1 - Mật khẩu");
    printf("\n2 - Tên chủ TK");
    printf("\n3 - Ngày sinh");
    printf("\n4 - Số CMND");
    printf("\n>>> "); scanf("%d", &sw);
    switch(sw)
    {
        case 1: 
        {
            printf("\nNhập MK mới: "); scanf("%s", &mk);
            while(strcmp(mk, a[x].MK) == 0)
            {
                printf("MK mới không được trùng với MK cũ, nhập lại: "); scanf("%s", &mk);
            }
            strcpy(a[x].MK, mk);
            printf(">> Đổi MK thành công <<");
            printf("\n%s", a[x].MK);
            break;
        }
        case 2: 
        {
            printf("\nNhập Tên mới: "); scanf("%[^\n]", &name); 
            strcpy(a[x].ten_chuTK, name);
            printf(">> Đổi tên thành công <<");
            break;
        }
        case 3: 
        {
            printf("\nNhập ngày sinh mới: "); scanf("%d/%d/%d", &d, &m, &y);
            a[x].ngay_sinh_chuTK.day = d;
            a[x].ngay_sinh_chuTK.month = m;
            a[x].ngay_sinh_chuTK.year = y;
            printf(">> Đổi ngày sinh thành công <<");
            break;
        }
        case 4: 
        {
            printf("\nNhập số CMND mới: "); scanf("%s", &cmnd);
            strcpy(a[x].cmnd, cmnd);
            printf(">> Đổi số CMND thành công <<");
            break;
        }
    }
    return;
}

void trans_history(cus a[], int n, int x)
{
    printf("\n----- Lịch sử biến động số dư -----\n");
    int b = 1;
    for(int i=a[x].soBD-1; i>-1; i--)
    {
        printf("\n........Giao dịch %d........", b);
        printf("\nNgày: %d/%d/%d", a[x].BD_soDu[i].trans_day.day, a[x].BD_soDu[i].trans_day.month, a[x].BD_soDu[i].trans_day.year);
        printf("\nLoại giao dịch: ");
        if(a[x].BD_soDu[i].trans_type == 1) printf("Gửi tiền");
        else printf("Rút tiền");
        printf("\nSố tiền giao dịch: %.0lf", a[x].BD_soDu[i].trans_amount);
        printf("\nSố dư %.0lf", a[x].BD_soDu[i].current_balance);
        printf("\n");
        b++;
    }
}

void deleteAccount(cus a[], int *n, int x)
{
    int sw;
    printf("\n-Bạn có chắc là muốn xoá tài khoản này không-");
    printf("\n 1 - Đồng ý");
    printf("\n 2 - Huỷ");
    printf("\n>>> "); scanf("%d", &sw);
    if(sw == 1)
    {
        for(int i = x; i<*n; i++)
        {
            a[i] = a[i+1];
        }
        *n -= 1;
        printf("\n-Xoá tài khoản thành công-");
    }
    else
    {
        printf("\n-Huỷ thao tác-");
    }
}

void backupData(cus a[], ad adm[], int n, int nn)
{
    FILE *f = fopen("banking.txt", "w");
    fprintf(f, "Banking System\n");
    for(int i=0; i<nn; i++)
    {
        fprintf(f, "#%s|%s|%d/%d/%d|%s\n", adm[i].tenTK, adm[i].mk, adm[i].ngay_taoTK.day, adm[i].ngay_taoTK.month, 
        adm[i].ngay_taoTK.year, adm[i].tenAd);
    }
    for(int i=0; i<n; i++)
    {
        fprintf(f, "=%s|%s|%d/%d/%d|%s|%d/%d/%d|%s|%d|", a[i].soTK, a[i].MK, 
        a[i].ngay_taoTK.day, a[i].ngay_taoTK.month, a[i].ngay_taoTK.year,
        a[i].ten_chuTK, a[i].ngay_sinh_chuTK.day, a[i].ngay_sinh_chuTK.month, a[i].ngay_sinh_chuTK.year,
        a[i].cmnd, a[i].flag);
        for(int j=0; j<a[i].soBD; j++)
        {
            fprintf(f, "*%d/%d/%d-%d-%.0lf-%.0lf", a[i].BD_soDu[j].trans_day.day, a[i].BD_soDu[j].trans_day.month, a[i].BD_soDu[j].trans_day.year,
            a[i].BD_soDu[j].trans_type, a[i].BD_soDu[j].trans_amount, a[i].BD_soDu[j].current_balance);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void menu_cus(cus a[], ad adm[], int n, int nn)
{
    int sw1, sw2 = 0, x;
    while (1)
    {
        printf("\n\n-----------------------------------------");
        printf("\n   CÁC CHỨC NĂNG DÀNH CHO KHÁCH HÀNG");
        printf("\n 1 - Đăng nhập tài khoản");
        printf("\n 2 - Tạo tài khoản");
        printf("\n 3 - Giao dịch");
        printf("\n 4 - Xem thông tin tài khoản");
        printf("\n 5 - Thiết lập thông tin tài khoản");
        printf("\n 6 - Lịch sử biến động số dư");
        printf("\n 7 - Xoá tài khoản");
        printf("\n 8 - Thoát");
        printf("\nNhập chức năng: "); scanf("%d", &sw1);
        switch(sw1)
        {
            case 1: 
            {
                x = login(a, n);
                sw2 = 1;
                if(x == -1) backupData(a, adm, n, nn); 
                break;
            }
            case 2: 
            {
                if(sw2 == 1) printf("\nError");
                else
                {
                    createAccount(a, &n); 
                }
                break;
            }
            case 3: 
            {
                if(sw2 == 0) printf("\nHãy đăng nhập tài khoảng ngân hàng trước");
                else transaction(a, n, x); 
                break;
            }
            case 4: 
            {
                if(sw2 == 0) printf("\nHãy đăng nhập tài khoảng ngân hàng trước");
                else infor(a, n, x); 
                break;
            }
            case 5: 
            {
                if(sw2 == 0) printf("\nHãy đăng nhập tài khoảng ngân hàng trước");
                else inforSettings(a, n, x); 
                break;
            }
            case 6: 
            {
                if(sw2 == 0) printf("\nHãy đăng nhập tài khoảng ngân hàng trước");
                else trans_history(a, n, x); 
                break;
            }
            case 7:
            {
                if(sw2 == 0) printf("\nHãy đăng nhập tài khoảng ngân hàng trước");
                else deleteAccount(a, &n, x); 
                break;
            }
            case 8: 
            {
                printf("\n--Kết thúc phiên làm việc--"); sw1 = 0; 
                break;           
            }
        }
        if (sw1 == 0 || x == -1) 
        {
            backupData(a, adm, n, nn);
            return;
        }
    }
}

void cus_list(cus a[], ad adm[], int n, int nn)
{
    printf("\n----- Danh sách tài khoản ngân hàng -----");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    printf("\n| STT | Số tài khoản  | Ngày lập TK   | Tên chủ TK    | Số CMND   | Tình trạng |");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    for(int i=0; i<n; i++)
    {
        printf("\n| %-4d| %-14s| %-2d/%-2d/%-4d    | %-14s| %-10s", 
        i+1, a[i].soTK, a[i].ngay_taoTK.day, a[i].ngay_taoTK.month, a[i].ngay_taoTK.year, a[i].ten_chuTK, a[i].cmnd); 
        if(a[i].flag == 1) printf("| Bị khoá    |");
        else printf("| Ko bị khoá |");
        printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    }
}

void ad_list(ad adm[], int nn)
{
    printf("\n----- Danh sách tài khoản QTV -----");
    printf("\n+-----+---------------+---------------+---------------+");
    printf("\n| STT | Tên tài khoản | Ngày lập TK   | Tên Admin     |");
    printf("\n+-----+---------------+---------------+---------------+");
    for(int i=0; i<nn; i++)
    {
        printf("\n| %-4d| %-14s| %-2d/%-2d/%-4d    | %-14s|", i+1, 
        adm[i].tenTK, adm[i].ngay_taoTK.day, adm[i].ngay_taoTK.month, adm[i].ngay_taoTK.year, adm[i].tenAd);
        printf("\n+-----+---------------+---------------+---------------+");
    }
}

void lock_acc(cus a[], ad adm[], int n, int nn)
{
    char tk[11];
    printf("\n----- Khoá tài khoản ----");
    printf("\n Nhập số tài khoản muốn khoá: "); scanf("%s", &tk);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, tk) == 0) x = i;
    }
    while(x == -1)
    {
        printf("Số TK không tồn tại, nhập lại: "); scanf("%s", &tk);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, tk) == 0) x = i;
        }
    }
    a[x].flag = 1;
    printf("\n>>> Khoá tài khoản thành công <<<");
}

void unlock_acc(cus a[], ad adm[], int n, int nn)
{
    char tk[11];
    printf("\n----- Mở khoá tài khoản ----");
    printf("\n Nhập số tài khoản muốn mở khoá: "); scanf("%s", &tk);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, tk) == 0) x = i;
    }
    while(x == -1)
    {
        printf("Số TK không tồn tại, nhập lại: "); scanf("%s", &tk);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, tk) == 0) x = i;
        }
    }
    a[x].flag = 0;
    printf("\n>>> Mở khoá tài khoản thành công <<<");
}

void add_acc(ad adm[], int *nn, int w)
{
    int sw, r, sw1;
    if(w != 0)
    {
        printf("\n---- Tài khoản của bạn ko có quyền thực hiện chức năng này ----");
        return;
    }
    printf("\n----- Thêm/Xoá tài khoản Admin -----");
    printf("\n 1 - Thêm tài khoản");
    printf("\n 2 - Xoá tài khoản");
    printf("\n>>> "); scanf("%d", &sw);
    if(sw == 1)
    {
        char newAcc[9];
        srand((unsigned int)time(NULL));
        do
        {
            strcpy(newAcc, "Ad");
            char s[7];
            r = GetRandom(100000, 999999);
            itoa(r, s, 10);
            strcat(newAcc, s);
            printf("\nTên tài khoản đề xuất: %s", newAcc);
            printf("\n 1 - Đồng ý");
            printf("\n 2 - Tên khác");
            printf("\n>>> "); scanf("%d", &sw1);
        }while(sw1 == 2);
        strcpy(adm[*nn].tenTK, newAcc);
        printf("Nhập mật khẩu: "); scanf("%s", adm[*nn].mk);
        while(strlen(adm[*nn].mk) != 6)
        {
            printf("Nhập lại mật khẩu: "); scanf("%s", &adm[*nn].mk);
        }
        fflush(stdin);
        printf("Nhập tên Admin: "); scanf("%s", &adm[*nn].tenAd);
        adm[*nn].ngay_taoTK = specify_today();
        printf("\n>>> Thêm tài khoản QTV thành công <<<");
        *nn += 1;
    }
    else
    {
        char tk[9];
        printf("\nNhập số tài khoản muốn xoá: "); scanf("%s", &tk);
        int x = -1;
        for(int i=0; i<*nn; i++)
        {
            if(strcmp(adm[i].tenTK, tk) == 0) x = i;
        }
        while(x == -1)
        {
            printf("Số TK không tồn tại, nhập lại: "); scanf("%s", &tk);
            for(int i=0; i<*nn; i++)
            {
                if(strcmp(adm[i].tenTK, tk) == 0) x = i;
            }
        }
        printf("\n--Xác nhận xoá tài khoản %s--", adm[x].tenTK);
        printf("\n 1 - Xác nhận");
        printf("\n 2 - Huỷ");
        printf("\n>>> "); scanf("%d", &sw1);
        if(sw1 == 1)
        {
            for(int i=x; i<*nn; i++)
            {
                adm[i] = adm[i+1];
            }
            *nn -= 1;
            printf("\n>>> Xoá tài khoản thành công <<<");
        }
        else
        {
            printf("\n>>> Huỷ thao tác <<<");
            return;
        }
    }
}

void menu_ad(cus a[], ad adm[], int n, int nn)
{
    char tk[9], mk[7];
    int w = -1;
    // printf("\nn%d", n);
    // printf("\nnn%d", nn);
    printf("\n--- Hãy đăng nhập tài khoản quản trị viên ---");
    printf("\nNhập tên tài khoản: "); scanf("%s", &tk);
    for(int i=0; i<nn; i++)
    {
        if(strcmp(adm[i].tenTK, tk) == 0) w = i;
    }
    while(w == -1)
    {
        printf("Tài khoản không tồn tại, nhập lại: "); scanf("%s", &tk);
        for(int i=0; i<nn; i++)
        {
            if(strcmp(adm[i].tenTK, tk) == 0) w = i;
        }
    }
    printf("Nhập mật khẩu: "); scanf("%s", &mk);
    while(strcmp(adm[w].mk, mk) != 0)
    {
        printf("Mật khẩu không đúng, nhập lại: "); scanf("%s", &mk);
    }
    printf("\n>>> Đăng nhập thành công <<<");
    printf("\n  Xin chào %s", adm[w].tenAd);
    int sw, sw1 = 0;
    while(1)
    {
        printf("\n\n===== Các chức năng dành cho quản trị viên =====");
        printf("\n 1 - Danh sách các tài khoản ngân hàng");
        printf("\n 2 - Danh sách các tài khoản QTV");
        printf("\n 3 - Khoá tài khoản NH");
        printf("\n 4 - Mở khoá tài khoản NH");
        printf("\n 5 - Thêm, xoá tài khoản QTV");
        printf("\n 6 - Thoát");
        printf("\nNhập chức năng: "); scanf("%d", &sw);
        switch(sw)
        {
            case 1: cus_list(a, adm, n, nn); break;
            case 2: ad_list(adm, nn); break;
            case 3: lock_acc(a, adm, n, nn); sw1 = 1; break;
            case 4: unlock_acc(a, adm, n, nn); sw1 = 1; break;
            case 5: add_acc(adm, &nn, w); sw1 = 1; break;
            case 6: printf("\n----- Kết thúc -----"); break;
        }
        if(sw1 == 1 && sw == 6)
        {
            backupData(a, adm, n, nn);
            return;
        }
    }
}

void main() 
{
    char tk[11];
    int sw1, sw2 = 0, x;
    cus a[100];
    ad adm[100];
    printf("\n+=================================================+");
    printf("\n|         CHƯƠNG TRÌNH HỆ THỐNG NGÂN HÀNG         |");
    printf("\n+=================================================+");
    while(1)
    {
        int n = input_cus(a);
        int nn = input_ad(adm);
        int sw;
        printf("\n\nMenu chức năng");
        printf("\n========================================");
        printf("\n 1 - Chức năng cho khách hàng");
        printf("\n 2 - Chức năng cho quản trị viên");
        printf("\n 3 - Thoát");
        printf("\nNhập chức năng: "); scanf("%d", &sw);
        switch (sw)
        {
            case 1: menu_cus(a, adm, n, nn); break;
            case 2: menu_ad(a, adm, n, nn); break;
            case 3: printf("\n~~~~~~~ Kết thúc chương trình ~~~~~~~"); return;
        }
    }
}