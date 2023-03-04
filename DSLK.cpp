#include <iostream>
#include <bits/stdc++.h>
#include <time.h>
using namespace std;

// Mỗi node là 1 con trỏ kiểu node được cấp phát động
struct node
{
    int data;
    node *next;// Khai báo địa chỉ cho node tiếp theo
};

// Hàm tạo node mới dựa trên node sẵn có
node *make_node(int x) // x ở đây là dữ liệu sẽ được truyền vào phần data của node mới
{
    // Thực hiện cấp phát động cho con trỏ
    // node new_node* = (node*)malloc(sizeof(node);
    node *new_node = new node();
    new_node->data = x;
    new_node->next = NULL;
    return new_node;
}

// Duyệt và in data của các node
void duyet(node *head)// truyền vào node đầu tiên của danh sách là head
{
    if(head == NULL) 
    {
        cout << "=)))" << endl;
        return;
    }
    while(head != NULL)
    {
        // cout << "-" ;
        if(head->next == NULL) cout << head->data;
        else cout << head->data << " | ";
        head = head->next;
    }
}

// Đếm số node
int count(node *head)
{
    int c = 0;
    while(head != NULL)
    {
        c++;
        head = head->next;
    }
    return c;
}

// Thêm node vào đầu DSLK
void pushF(node **head, int x)
{
    node *new_node = make_node(x);
    new_node->next = *head; // Giải tham chiếu. *head lưu địa chi của node head.
    *head = new_node; // Cập nhật node head = newnode
}

// Thêm node vào cuối DSLK
void pushB(node **head, int x)
{
    node *new_node = make_node(x);
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
}

// Thêm node vào vị trí bất kì trong DSLK
void insert(node **head, int k, int x)
{
    int n = count(*head);
    if(k<1 || k>n+1) return;
    if(k == 1)
    {
        pushF(head, x);
        return;
    }
    node *tmp = *head;
    for(int i=1; i<=k-2; i++)
    {
        tmp = tmp->next;
    }
    node *new_node = make_node(x);
    new_node->next = tmp->next;
    tmp->next = new_node;
}

// Tính tổng của data của các node
int sum_list(node *head)
{
    int sum = 0;
    while(head != NULL)
    {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

// Xoá node ở vị trí cho trước
void delete_ele(node **head, int k)
{
    int n = count(*head);
    node *tmp = *head;
    if(k<1 || k>n) return;
    else if(k == 1)
    {
        *head = tmp->next;
        return;
    }
    for(int i=1; i<=k-2; i++)
    {
        tmp = tmp->next;
    }
    node *tmp1 = tmp->next->next;
    tmp->next = tmp1;
}

// Tìm node ở vị trí cho trước
node *search_node(node *head, int k)
{
    int n = count(head);
    for(int i=1; i<=k-1; i++)
        head = head->next;
    node *tmp = head;
    return tmp;
}

void change_data(node *head, int x)
{
    head->data = x;
    return;
}

// Sắp xếp data của các node
void sort(node **head)
{
    for(node *i = *head; i != NULL; i = i->next)// Duyệt qua tất cả các node
    {
        node *min_node = i;
        for(node *j = i->next; j != NULL; j = j->next)
        {
            if(min_node->data > j->data)
                min_node = j;
        }
        int tmp = min_node->data;// Hoán đổi data của min_node và i
        min_node->data = i->data;
        i->data = tmp;
    }
}

int main()
{
    node *head = NULL;
    // for(int i=5; i>=0; i--)
    // {
    //     pushB(&head, i);
    // }
    // duyet(head);
    while(1)
    {
        cout << "\n1 - Chen";
        cout << "\n2 - Xoa";
        cout << "\n3 - Search";
        cout << "\n4 - Sort";
        cout << "\n>> ";
        int v; cin >> v;
        if(v == 1)
        {    
            while(1)
            {
                int sw;
                cout << "\n1 - Chen vao dau";
                cout << "\n2 - Chen vao cuoi";
                cout << "\n3 - Chen vao vi tri xac dinh";
                cout << "\n>> "; cin >> sw;
                if(sw == 1)
                {
                    int x;
                    cout << "Gia tri: "; cin >> x;
                    pushF(&head, x);
                }
                else if(sw == 2)
                {
                    int x;
                    cout << "Gia tri: "; cin >> x;
                    pushB(&head, x);
                }
                else if(sw == 3)
                {
                    int x, k;
                    cout << "Gia tri: "; cin >> x;
                    cout << "Vi tri: "; cin >> k;
                    insert(&head, k, x);
                }
                else break;
                duyet(head);
            }  
        }
        else if(v == 2)
        {
            int k;
            cout << "Vi tri: ";
            cin >> k;
            delete_ele(&head, k);
            duyet(head);
        }
        else if(v == 3)
        {
            int k;
            cout << "Search index: ";
            cin >> k;
            node *node_S = search_node(head, k);
            cout << "Node "<< k <<" data: "<<  node_S->data << endl;
        }
        else if(v == 4)
        {
            sort(&head);
            duyet(head);
        }
        else break;
    }
    // cout << endl;
    // // cout << "\nSum: " << sum_list(head);
    // int k;
    // int x;
    // cout << "value: "; cin >> x;
    // change_data(head, x);
    // duyet(head);
    return 0;
}
