#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<iomanip>
#include<windows.h>
#include<stdio.h>
using namespace std;

struct date
{
    int day;
    int month;
    int year;
};

struct bdsd
{
    date date; //Ngày thực hiện giao dịch
    int type; //Loại giao dịch(1-Gửi tiền ; 0-Rút tiền)
    float amou; //Số tiền giao dịch
    float bal; //Số dư sau giao dịch
};

struct cus
{
    string stk; //Số tài khoản
    string mk; // Mật khẩu
    string name; // tên người dùng
    date ngay; // ngày lập tk
    string cmnd; // số cmnd
    int cond;
    float bal; // số dư hiện tại
    vector<bdsd> bdsd; // các lần biến động số dư
};

struct node
{
    cus data;
    node *next;
};

node *make_node(cus data)
{
    node *new_node = new node();// cấp phát động
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

int size_(node *head)
{
    int c = 0;
    while(head->next != NULL)
    {
        head = head->next;
        ++c;
    }
    return c;
}

void push_back(node **head, cus data)
{
    node *new_node = make_node(data);
    if(*head == NULL)
    {
        *head = new_node;
        return;
    }
    node *tmp = *head;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
    return;
}

node *head_cus = NULL;
bool check_mk(string mk, string mki)
{
    if(mk == mki) return true;
    else return false;
}
int GetRandom(int min,int max)// Hàm lấy random các số từ min đến max
{
    return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}
date today()
{
    date today;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    today.day = tm.tm_mday;
    today.month = tm.tm_mon + 1;
    today.year = tm.tm_year + 1900;
    return today;
}

char* convert_number(float x)
{
    char *s; 
    itoa(x, s, 10);
    // printf("%s", s);
    return s;
}

// cho hàm trả về node của tài khoản được đăng nhập, trả về NULL khi chưa đăng nhập
node* login(node *head)
{
    string stk, mk;
    cout << "Account number: "; cin >> stk;
    while(1)
    {
        if(head == NULL) 
        {
            cout << "[ERROR]";
            return NULL;
        }
        else if(head->data.stk == stk)
        {
            if(head->data.cond == 1)
            {
                cout << ">>> YOUR ACCOUNT WAS LOCKED <<<" << endl;
                return NULL;
            }
            cout << "Password: ";
            cin >> mk;
            int ct = 5;
            if(!check_mk(head->data.mk, mk))
            {   
                while(ct > 1)
                {
                    cout << "Incorrect password. Re-enter ("<< ct << " left): ";
                    cin >> mk;
                    ct--;
                    if(check_mk(head->data.mk, mk))       
                        break;
                }
            }
            if(ct == 1) 
            {
                cout << "TOO MANY FALSE ATTEMPTS, YOUR ACCOUNT WAS LOCKED." << endl;
                head->data.cond = 1;
                return NULL;
            }
            else
            {
                cout << ">>> Login successfully <<<" << endl;
                return head;
            }
        }
        if(head->next == NULL)
        {
            cout << "[ERROR, Account not found]" << endl;
            return NULL;
        }
        head = head->next;
    }
} 

void new_account(node **head)
{
    int sw1 = 0;
    string mkx;
    cus tm;
    do
    {
        tm.stk = "704";
        do
        {
            int x = GetRandom(0, 9);
            tm.stk += to_string(x);
        } while (tm.stk.length() <= 9);
        cout << tm.stk << endl;
        cout << "Accept? (1 - Accept ; 0 - Decline)>>> ";
        cin >> sw1;
    } while(!sw1);
    cout << "Enter password: " ;
    cin >> tm.mk;
    do
    {
        cout << "Confirm your password: ";
        cin >> mkx;
    } while(mkx != tm.mk);
    cout << "Enter name: " ;
    cin >> tm.name;
    cout << "Enter ID number: ";
    cin >> tm.cmnd;
    tm.ngay = today();
    tm.bal = 50000;
    bdsd bd;
    bd.date = today();
    bd.type = 1;
    bd.amou = 50000;
    bd.bal = 50000;
    tm.bdsd.push_back(bd);
    tm.cond = 0;
    
    push_back(head, tm);
    cout << ">>> Account created successfully <<<" << endl;
}

void SET_COLOR(int color)
{
	WORD wColor;
     

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
}

void info(node *cur)
{
    cout << "\n=== Information ===" << endl;
    cout << "Account number: " << cur->data.stk << endl;
    cout << "Password: " << cur->data.mk << endl;
    cout << "Customer name: " << cur->data.name << endl;
    cout << "Customer ID number: " << cur->data.cmnd << endl;
    cout << "Account creation dates: " << cur->data.ngay.day << "/" << cur->data.ngay.month << "/" << cur->data.ngay.year << endl;
    cout << "Account condition: ";
    if(cur->data.cond == 1) cout << "Locked" << endl;
    else cout << "Normal" << endl;
    cout << "Balance: " << cur->data.bal << endl;
    cout << "Blance fluctuations: " << endl;
    cout << "------------------" << endl;
    for(int i=0; i<cur->data.bdsd.size(); i++)
    {
        cout << "Dates: " << cur->data.bdsd[i].date.day << "/" << cur->data.bdsd[i].date.month << "/" << cur->data.bdsd[i].date.year << endl;
        cout << "Amount: ";
        if(cur->data.bdsd[i].type == 1)
        {
            SET_COLOR(2);
            cout << "+" << convert_number(cur->data.bdsd[i].amou) << endl;
        }
        else 
        {
            SET_COLOR(4);
            cout << "-" << convert_number(cur->data.bdsd[i].amou) << endl;
        }
        SET_COLOR(7);
        cout << "Balance: " << convert_number(cur->data.bdsd[i].bal) << endl;
        cout << "------------------" << endl;
    }
}
    
void transfer(node *cur)
{
    int sw = 1;
    bdsd bd;
    cout << "=== Transfer ===" << endl;
    do{
        cout << "Enter type of transfer" << endl;
        cout << "1 - Deposit" << endl;
        cout << "2 - Withdraw" << endl;
        cout << ">>> " ; 
        cin >> bd.type;
        cout << "Enter amount of transfer: ";
        cin >> bd.amou;
        cout << "Transfer confirm" << endl;
        cout << "Type: ";
        if(bd.type == 1) cout << "Deposit";
        else cout << "Withdraw";
        cout << endl;
        cout << "Amount: " << bd.amou << endl;
        bd.date = today();
        
        int cf;
        cout << ">>> "; cin >> cf;
        if(cf == 0) 
        {
            cout << "Trasaction is cancelled" << endl;
            return;
        }
        else if(cf == 1)
        {
            int n = cur->data.bdsd.size();
            if(bd.type == 1)
                bd.bal = cur->data.bdsd[n-1].bal + bd.amou;
            else
                bd.bal = cur->data.bdsd[n-1].bal - bd.amou;
            cur->data.bal = bd.bal;
            cur->data.bdsd.push_back(bd);
            cout << "Transaction completed" << endl;
        }
        cout << "----------------------------" << endl;
        cout << "Continue >>> "; cin >> sw;
    }while(sw);
}

int main()
{
    node *head = NULL;
    node *cur = NULL; 
    string stk = "";
    int sw, sw1;
    // push_back(&head, model);
    do
    {
        cout << "\n1 - Login" << endl;
        cout << "2 - Transfer" << endl;
        cout << "3 - Information" << endl;
        cout << ">>> "; cin >> sw;
        // cout << endl;
        if(sw == 1)
        {
            cout << "\n=== Login ===";
            cout << "\n1 - Login";
            cout << "\n2 - New account";
            cout << "\n>>> ";
            cin >> sw1;
            if(sw1 == 1) cur = login(head);
            else if (sw1 == 2) new_account(&head);
        }
        else if(sw == 2)
        {
            if(cur == NULL) 
            {
                cout << "ERROR. Login first\n" << endl;
                continue;
            }
            transfer(cur);
        }
        else if(sw == 3)
        {
            if(cur == NULL) 
            {
                cout << "ERROR. Login first\n" << endl;
                continue;
            }
            info(cur);
        }
    }while (sw != 0);
    
}