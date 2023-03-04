#include<stdio.h>
#include<string.h>

typedef struct ques
{
    long ID;
    int chapter;
    char content[50];
}ques;

int read(ques a[])
{
    int n;
    printf("\nInput number of questions: "); scanf("%d", &n);
    while(n<0 || n>100)
    {
        printf("\nMust be > 0 and <=100. Try again: "); scanf("%d", &n);
    }
    printf("\nEnter the question with the following format: Chapter Content");
    for(int i=0; i<n; i++)
    {
        printf("\nQuestion %d: \n",i+1);
        scanf("%d %[^\n]", &a[i].chapter, a[i].content);
        a[i].ID = i+1;
    }
    printf("\nQuestions list\n");
    printf("%s\t%s\t%s\n","ID","Chap","Content");
    printf("========================================================================\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t\"%s\"\n", a[i].ID, a[i].chapter, a[i].content);
        printf("------------------------------------------------------------------------\n");
    }
}

void search(ques a[], int n)
{
    int id, ct = 0;
    printf("\nSearch for ID\n");
    printf("Input ID: ");scanf("%d",&id);
    for(int i=0; i<n; i++)
    {
        if(a[i].ID == id)
        {
            printf("%s\t%s\t%s\n","ID","Chap","Content");
            printf("========================================================================\n");
            printf("%d\t%d\t\"%s\"\n", a[i].ID, a[i].chapter, a[i].content);
            printf("------------------------------------------------------------------------\n");
            ct = 1;
        }
    }
    if(ct == 0)
    {
        printf("\nID not found");
    }
}

int add(ques a[], int n)
{
    int cpt;
    char ctn[50];
    printf("\nAdd a question\n");
    printf("\nEnter the question with the following format: Chapter Content\n");
    scanf("%d %[^\n]", &cpt, ctn);
    a[n].chapter = cpt;
    strcpy(a[n].content, ctn);
    a[n].ID = n+1;
    n++;
    printf("\nQuestions list\n");
    printf("%s\t%s\t%s\n","ID","Chap","Content");
    printf("=========================================================================\n");
    for(int i=0; i<n; i++)
    {
        printf("%d\t%d\t\"%s\"\n", a[i].ID, a[i].chapter, a[i].content);
        printf("-------------------------------------------------------------------------\n");
    }
    return n;
}

void count(ques a[], int n)
{   
    printf("\nCount\n");
    int in = 0;
    printf("%s\t%s\n","Chap","Count");
    printf("==================\n");
    for(int i=0; i<n; i++)
    {
        int cnt = 0;
        for(int j=0; j<i; j++)
        {
            if(a[j].chapter == a[i].chapter)
            in = 1;
        }
        if(in == 0)
        {
            for(int k=0; k<n; k++)
            {
                if(a[k].chapter == a[i].chapter) cnt++;
            }
        }
        printf("%d\t%d\n",a[i].chapter, cnt);
        printf("------------------\n");
    }
}

void check (ques a[], int n)
{
    printf("\nValid questions\n");
    printf("%s\t%s\t%s\n","ID","Chap","Content");
    printf("========================================================================\n");
    for(int i=0; i<n; i++)
    {
        int ck = 0;
        int len = strlen(a[i].content);
        for(int j=0; j<len; j++)
        {
            if(a[i].content[j]=='*' || a[i].content[j]=='$' || a[i].content[j]=='\\') ck = 1;
        }
        if(a[i].content[0] >= 'a' && a[i].content[0] <= 'z') ck = 1;
        if(ck == 0)
        {
            printf("%d\t%d\t\"%s\"\n", a[i].ID, a[i].chapter, a[i].content);
            printf("------------------------------------------------------------------------\n");
        }
    }
}


void main()
{
    int sw = 0, n, c = 0;
    ques array[100];
    while (1)
    {
        printf("\n\nMenu functions");
        printf("\n1-Read");
        printf("\n2-Search");
        printf("\n3-Add");
        printf("\n4-Count");
        printf("\n5-Check");
        printf("\n6-Exit");
        printf("\nFunction: "); scanf("%d", &sw);

        switch(sw)
        {
            case 1: n = read(array); break;
            case 2: search(array, n); break;
            case 3: n = add(array, n); break;
            case 4: count(array, n); break;
            case 5: check(array, n); break;
            case 6: printf("\n>>>>> End Program <<<<<\n\n"); c = 1; break;
        }
        if (c == 1) break;
    }
    
}
