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
    printf("\n----????ng nh???p t??i kho???n----");
    printf("\nNh???p s??? TK: "); scanf("%s", &s);
    fflush(stdin);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, s) == 0) x = i;
    }
    while(x == -1)
    {
        printf("S??? TK kh??ng t???n t???i, nh???p l???i: "); scanf("%s", &s);
        fflush(stdin);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, s) == 0) x = i;
        }
    }
    if(a[x].flag == 1) 
    {
        printf("\n");
        printf("----- T??i kho???n ???? b??? kho?? -----");
        return -1;
    }
    else
    {
        printf("Nh???p m???t kh???u: "); scanf("%s", &mk);
        int lan_nhap = 5;
        while(strcmp(mk, a[x].MK) != 0)
        {
            printf("Nh???p sai m???t kh???u, h??y nh???p l???i (c??n %d l???n nh???p): ", lan_nhap); scanf("%s", &mk);
            lan_nhap--;
            if(lan_nhap == 0)
            {
                printf("B???n ???? nh???p sai m???t kh???u qu?? nhi???u l???n. T??i kho???n c???a b???n s??? b??? kho??"); 
                a[x].flag = 1; 
                return -1;
            }
        }
    }
    printf("\n<<<????ng nh???p th??nh c??ng>>>");
    printf("\nXin ch??o %s", a[x].ten_chuTK); 
    return x;
}

int GetRandom(int min,int max)// H??m l???y random c??c s??? t??? min ?????n max
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
    printf("\n-----T???o t??i kho???n-----");
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
        printf("\nS??? t??i kho???n ????? xu???t: %s", news);
        printf("\n1 - Ch???p nh???n");
        printf("\n2 - ?????i s???");
        printf("\n>>> ");
        scanf("%d", &sw);
    } while (sw == 2);
    strcpy(a[*n].soTK, news);
    printf("Nh???p m???t kh???u: "); scanf("%s", &a[*n].MK);
    while(strlen(a[*n].MK) != 6)
    {
        printf("Nh???p l???i m???t kh???u: "); scanf("%s", &a[*n].MK);
    }
    fflush(stdin);
    printf("Nh???p t??n ch??? TK: "); scanf("%[^\n]", &a[*n].ten_chuTK);
    a[*n].ngay_taoTK = specify_today();
    printf("Nh???p ng??y sinh (dd/mm/yyyy): "); scanf("%d/%d/%d",&a[*n].ngay_sinh_chuTK.day, &a[*n].ngay_sinh_chuTK.month, &a[*n].ngay_sinh_chuTK.year);
    printf("Nh???p s??? CMND: "); scanf("%s", &a[*n].cmnd);
    a[*n].flag = 0;
    a[*n].BD_soDu[0].trans_day = specify_today();
    a[*n].BD_soDu[0].trans_type = 1;
    a[*n].BD_soDu[0].trans_amount = 50000;
    a[*n].BD_soDu[0].current_balance = 50000;
    a[*n].soDu = 50000;
    a[*n].soBD = 1;
    printf("\n>> T???o t??i kho???n th??nh c??ng <<");
    printf("\nSTK: %s", a[*n].soTK);
    printf("\nMK: %s", a[*n].MK);
    printf("\nNg??y t???o t??i kho???n: %d/%d/%d", a[*n].ngay_taoTK.day, a[*n].ngay_taoTK.month, a[*n].ngay_taoTK.year);
    printf("\nT??n ch??? TK: %s", a[*n].ten_chuTK);
    printf("\nNg??y sinh: %d/%d/%d", a[*n].ngay_sinh_chuTK.day, a[*n].ngay_sinh_chuTK.month, a[*n].ngay_sinh_chuTK.year);
    printf("\nS??? CMND: %s", a[*n].cmnd);
    printf("\nS??? d??: %.0lf", a[*n].soDu);
    printf("\n>> H??y ????ng nh???p l???i <<");
    *n += 1;
}

void transaction(cus a[], int n, int x)
{
    int sw, sw1 = 0;
    double t;
    printf("\n       -----Giao d???ch-----");
    printf("\nNh???p lo???i giao d???ch (1-G???i ti???n;0-R??t ti???n): "); scanf("%d", &sw);
    printf("Nh???p s??? ti???n giao d???ch: "); scanf("%lf", &t);
    printf("\nX??c nh???n giao d???ch");
    if(sw == 1) printf("\nLo???i giao d???ch: G???i ti???n");
    else printf("\nLo???i giao d???ch: R??t ti???n");
    printf("\nS??? ti???n: %.0lf", t);
    printf("\n(1-?????ng ??; 0-T??? ch???i) "); scanf("%d", &sw1);
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
                printf("\n>>> Giao d???ch th???t b???i, s??? d?? kh??ng ????? <<<");
                return;
            }
            a[x].BD_soDu[y].current_balance = a[x].soDu - t;
            a[x].BD_soDu[y].trans_type = 0;
        }
        a[x].soDu = a[x].BD_soDu[y].current_balance;
        a[x].soBD++;
        printf("\n>>> Giao d???ch th??nh c??ng <<<");
        printf("\nS??? d?? hi???n t???i: %.0lf", a[x].soDu);
        // printf("\nNg??y: %d/%d/%d", a[x].BD_soDu[y].trans_day.day, a[x].BD_soDu[y].trans_day.month, a[x].BD_soDu[y].trans_day.year);
        // printf("\nSB??: %d", a[x].soBD);
    }
    else printf("\n>>> Hu??? giao d???ch <<<");
}

void infor(cus a[], int n, int x)
{
    printf("\n-----Th??ng tin t??i kho???n-----");
    printf("\nS??? t??i kho???n: %s", a[x].soTK);
    printf("\nM???t kh???u: %s", a[x].MK);
    printf("\nNg??y t???o t??i kho???n: %d/%d/%d", a[x].ngay_taoTK.day, a[x].ngay_taoTK.month, a[x].ngay_taoTK.year);
    printf("\nT??n ch??? TK: %s", a[x].ten_chuTK);
    printf("\nNg??y sinh: %d/%d/%d", a[x].ngay_sinh_chuTK.day, a[x].ngay_sinh_chuTK.month, a[x].ngay_sinh_chuTK.year);
    printf("\nS??? CMND: %s", a[x].cmnd);
}

void inforSettings(cus a[], int n, int x)
{
    int sw, d, m, y;
    char mk[7], name[20], cmnd[10];
    printf("\n-----S???a ?????i th??ng tin-----");
    printf("\nNh???p th??ng tin mu???n s???a");
    printf("\n1 - M???t kh???u");
    printf("\n2 - T??n ch??? TK");
    printf("\n3 - Ng??y sinh");
    printf("\n4 - S??? CMND");
    printf("\n>>> "); scanf("%d", &sw);
    switch(sw)
    {
        case 1: 
        {
            printf("\nNh???p MK m???i: "); scanf("%s", &mk);
            while(strcmp(mk, a[x].MK) == 0)
            {
                printf("MK m???i kh??ng ???????c tr??ng v???i MK c??, nh???p l???i: "); scanf("%s", &mk);
            }
            strcpy(a[x].MK, mk);
            printf(">> ?????i MK th??nh c??ng <<");
            printf("\n%s", a[x].MK);
            break;
        }
        case 2: 
        {
            printf("\nNh???p T??n m???i: "); scanf("%[^\n]", &name); 
            strcpy(a[x].ten_chuTK, name);
            printf(">> ?????i t??n th??nh c??ng <<");
            break;
        }
        case 3: 
        {
            printf("\nNh???p ng??y sinh m???i: "); scanf("%d/%d/%d", &d, &m, &y);
            a[x].ngay_sinh_chuTK.day = d;
            a[x].ngay_sinh_chuTK.month = m;
            a[x].ngay_sinh_chuTK.year = y;
            printf(">> ?????i ng??y sinh th??nh c??ng <<");
            break;
        }
        case 4: 
        {
            printf("\nNh???p s??? CMND m???i: "); scanf("%s", &cmnd);
            strcpy(a[x].cmnd, cmnd);
            printf(">> ?????i s??? CMND th??nh c??ng <<");
            break;
        }
    }
    return;
}

void trans_history(cus a[], int n, int x)
{
    printf("\n----- L???ch s??? bi???n ?????ng s??? d?? -----\n");
    int b = 1;
    for(int i=a[x].soBD-1; i>-1; i--)
    {
        printf("\n........Giao d???ch %d........", b);
        printf("\nNg??y: %d/%d/%d", a[x].BD_soDu[i].trans_day.day, a[x].BD_soDu[i].trans_day.month, a[x].BD_soDu[i].trans_day.year);
        printf("\nLo???i giao d???ch: ");
        if(a[x].BD_soDu[i].trans_type == 1) printf("G???i ti???n");
        else printf("R??t ti???n");
        printf("\nS??? ti???n giao d???ch: %.0lf", a[x].BD_soDu[i].trans_amount);
        printf("\nS??? d?? %.0lf", a[x].BD_soDu[i].current_balance);
        printf("\n");
        b++;
    }
}

void deleteAccount(cus a[], int *n, int x)
{
    int sw;
    printf("\n-B???n c?? ch???c l?? mu???n xo?? t??i kho???n n??y kh??ng-");
    printf("\n 1 - ?????ng ??");
    printf("\n 2 - Hu???");
    printf("\n>>> "); scanf("%d", &sw);
    if(sw == 1)
    {
        for(int i = x; i<*n; i++)
        {
            a[i] = a[i+1];
        }
        *n -= 1;
        printf("\n-Xo?? t??i kho???n th??nh c??ng-");
    }
    else
    {
        printf("\n-Hu??? thao t??c-");
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
        printf("\n   C??C CH???C N??NG D??NH CHO KH??CH H??NG");
        printf("\n 1 - ????ng nh???p t??i kho???n");
        printf("\n 2 - T???o t??i kho???n");
        printf("\n 3 - Giao d???ch");
        printf("\n 4 - Xem th??ng tin t??i kho???n");
        printf("\n 5 - Thi???t l???p th??ng tin t??i kho???n");
        printf("\n 6 - L???ch s??? bi???n ?????ng s??? d??");
        printf("\n 7 - Xo?? t??i kho???n");
        printf("\n 8 - Tho??t");
        printf("\nNh???p ch???c n??ng: "); scanf("%d", &sw1);
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
                if(sw2 == 0) printf("\nH??y ????ng nh???p t??i kho???ng ng??n h??ng tr?????c");
                else transaction(a, n, x); 
                break;
            }
            case 4: 
            {
                if(sw2 == 0) printf("\nH??y ????ng nh???p t??i kho???ng ng??n h??ng tr?????c");
                else infor(a, n, x); 
                break;
            }
            case 5: 
            {
                if(sw2 == 0) printf("\nH??y ????ng nh???p t??i kho???ng ng??n h??ng tr?????c");
                else inforSettings(a, n, x); 
                break;
            }
            case 6: 
            {
                if(sw2 == 0) printf("\nH??y ????ng nh???p t??i kho???ng ng??n h??ng tr?????c");
                else trans_history(a, n, x); 
                break;
            }
            case 7:
            {
                if(sw2 == 0) printf("\nH??y ????ng nh???p t??i kho???ng ng??n h??ng tr?????c");
                else deleteAccount(a, &n, x); 
                break;
            }
            case 8: 
            {
                printf("\n--K???t th??c phi??n l??m vi???c--"); sw1 = 0; 
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
    printf("\n----- Danh s??ch t??i kho???n ng??n h??ng -----");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    printf("\n| STT | S??? t??i kho???n  | Ng??y l???p TK   | T??n ch??? TK    | S??? CMND   | T??nh tr???ng |");
    printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    for(int i=0; i<n; i++)
    {
        printf("\n| %-4d| %-14s| %-2d/%-2d/%-4d    | %-14s| %-10s", 
        i+1, a[i].soTK, a[i].ngay_taoTK.day, a[i].ngay_taoTK.month, a[i].ngay_taoTK.year, a[i].ten_chuTK, a[i].cmnd); 
        if(a[i].flag == 1) printf("| B??? kho??    |");
        else printf("| Ko b??? kho?? |");
        printf("\n+-----+---------------+---------------+---------------+-----------+------------+");
    }
}

void ad_list(ad adm[], int nn)
{
    printf("\n----- Danh s??ch t??i kho???n QTV -----");
    printf("\n+-----+---------------+---------------+---------------+");
    printf("\n| STT | T??n t??i kho???n | Ng??y l???p TK   | T??n Admin     |");
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
    printf("\n----- Kho?? t??i kho???n ----");
    printf("\n Nh???p s??? t??i kho???n mu???n kho??: "); scanf("%s", &tk);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, tk) == 0) x = i;
    }
    while(x == -1)
    {
        printf("S??? TK kh??ng t???n t???i, nh???p l???i: "); scanf("%s", &tk);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, tk) == 0) x = i;
        }
    }
    a[x].flag = 1;
    printf("\n>>> Kho?? t??i kho???n th??nh c??ng <<<");
}

void unlock_acc(cus a[], ad adm[], int n, int nn)
{
    char tk[11];
    printf("\n----- M??? kho?? t??i kho???n ----");
    printf("\n Nh???p s??? t??i kho???n mu???n m??? kho??: "); scanf("%s", &tk);
    int x = -1;
    for(int i=0; i<n; i++)
    {
        if(strcmp(a[i].soTK, tk) == 0) x = i;
    }
    while(x == -1)
    {
        printf("S??? TK kh??ng t???n t???i, nh???p l???i: "); scanf("%s", &tk);
        for(int i=0; i<n; i++)
        {
            if(strcmp(a[i].soTK, tk) == 0) x = i;
        }
    }
    a[x].flag = 0;
    printf("\n>>> M??? kho?? t??i kho???n th??nh c??ng <<<");
}

void add_acc(ad adm[], int *nn, int w)
{
    int sw, r, sw1;
    if(w != 0)
    {
        printf("\n---- T??i kho???n c???a b???n ko c?? quy???n th???c hi???n ch???c n??ng n??y ----");
        return;
    }
    printf("\n----- Th??m/Xo?? t??i kho???n Admin -----");
    printf("\n 1 - Th??m t??i kho???n");
    printf("\n 2 - Xo?? t??i kho???n");
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
            printf("\nT??n t??i kho???n ????? xu???t: %s", newAcc);
            printf("\n 1 - ?????ng ??");
            printf("\n 2 - T??n kh??c");
            printf("\n>>> "); scanf("%d", &sw1);
        }while(sw1 == 2);
        strcpy(adm[*nn].tenTK, newAcc);
        printf("Nh???p m???t kh???u: "); scanf("%s", adm[*nn].mk);
        while(strlen(adm[*nn].mk) != 6)
        {
            printf("Nh???p l???i m???t kh???u: "); scanf("%s", &adm[*nn].mk);
        }
        fflush(stdin);
        printf("Nh???p t??n Admin: "); scanf("%s", &adm[*nn].tenAd);
        adm[*nn].ngay_taoTK = specify_today();
        printf("\n>>> Th??m t??i kho???n QTV th??nh c??ng <<<");
        *nn += 1;
    }
    else
    {
        char tk[9];
        printf("\nNh???p s??? t??i kho???n mu???n xo??: "); scanf("%s", &tk);
        int x = -1;
        for(int i=0; i<*nn; i++)
        {
            if(strcmp(adm[i].tenTK, tk) == 0) x = i;
        }
        while(x == -1)
        {
            printf("S??? TK kh??ng t???n t???i, nh???p l???i: "); scanf("%s", &tk);
            for(int i=0; i<*nn; i++)
            {
                if(strcmp(adm[i].tenTK, tk) == 0) x = i;
            }
        }
        printf("\n--X??c nh???n xo?? t??i kho???n %s--", adm[x].tenTK);
        printf("\n 1 - X??c nh???n");
        printf("\n 2 - Hu???");
        printf("\n>>> "); scanf("%d", &sw1);
        if(sw1 == 1)
        {
            for(int i=x; i<*nn; i++)
            {
                adm[i] = adm[i+1];
            }
            *nn -= 1;
            printf("\n>>> Xo?? t??i kho???n th??nh c??ng <<<");
        }
        else
        {
            printf("\n>>> Hu??? thao t??c <<<");
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
    printf("\n--- H??y ????ng nh???p t??i kho???n qu???n tr??? vi??n ---");
    printf("\nNh???p t??n t??i kho???n: "); scanf("%s", &tk);
    for(int i=0; i<nn; i++)
    {
        if(strcmp(adm[i].tenTK, tk) == 0) w = i;
    }
    while(w == -1)
    {
        printf("T??i kho???n kh??ng t???n t???i, nh???p l???i: "); scanf("%s", &tk);
        for(int i=0; i<nn; i++)
        {
            if(strcmp(adm[i].tenTK, tk) == 0) w = i;
        }
    }
    printf("Nh???p m???t kh???u: "); scanf("%s", &mk);
    while(strcmp(adm[w].mk, mk) != 0)
    {
        printf("M???t kh???u kh??ng ????ng, nh???p l???i: "); scanf("%s", &mk);
    }
    printf("\n>>> ????ng nh???p th??nh c??ng <<<");
    printf("\n  Xin ch??o %s", adm[w].tenAd);
    int sw, sw1 = 0;
    while(1)
    {
        printf("\n\n===== C??c ch???c n??ng d??nh cho qu???n tr??? vi??n =====");
        printf("\n 1 - Danh s??ch c??c t??i kho???n ng??n h??ng");
        printf("\n 2 - Danh s??ch c??c t??i kho???n QTV");
        printf("\n 3 - Kho?? t??i kho???n NH");
        printf("\n 4 - M??? kho?? t??i kho???n NH");
        printf("\n 5 - Th??m, xo?? t??i kho???n QTV");
        printf("\n 6 - Tho??t");
        printf("\nNh???p ch???c n??ng: "); scanf("%d", &sw);
        switch(sw)
        {
            case 1: cus_list(a, adm, n, nn); break;
            case 2: ad_list(adm, nn); break;
            case 3: lock_acc(a, adm, n, nn); sw1 = 1; break;
            case 4: unlock_acc(a, adm, n, nn); sw1 = 1; break;
            case 5: add_acc(adm, &nn, w); sw1 = 1; break;
            case 6: printf("\n----- K???t th??c -----"); break;
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
    printf("\n|         CH????NG TR??NH H??? TH???NG NG??N H??NG         |");
    printf("\n+=================================================+");
    while(1)
    {
        int n = input_cus(a);
        int nn = input_ad(adm);
        int sw;
        printf("\n\nMenu ch???c n??ng");
        printf("\n========================================");
        printf("\n 1 - Ch???c n??ng cho kh??ch h??ng");
        printf("\n 2 - Ch???c n??ng cho qu???n tr??? vi??n");
        printf("\n 3 - Tho??t");
        printf("\nNh???p ch???c n??ng: "); scanf("%d", &sw);
        switch (sw)
        {
            case 1: menu_cus(a, adm, n, nn); break;
            case 2: menu_ad(a, adm, n, nn); break;
            case 3: printf("\n~~~~~~~ K???t th??c ch????ng tr??nh ~~~~~~~"); return;
        }
    }
}