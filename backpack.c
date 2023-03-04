// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// #define MAX_N 1000
// #define MAX_W 1000

// int N, W;
// int g[MAX_N], v[MAX_N];
// char name[MAX_N][10];
// int dp[MAX_W + 1];

// int main()
// {
//     FILE *f = fopen("BAG.INP", "r");
//     fscanf(f, "%d %d", &N, &W);
//     for (int i = 0; i < N; i++)
//     {
//         fscanf(f, "%d %d %s", &g[i], &v[i], name[i]);
//     }
//     fclose(f);

//     for (int i = 0; i < N; i++)
//     {
//         for (int j = g[i]; j <= W; j++)
//         {
//             if (dp[j] < dp[j - g[i]] + v[i])
//             {
//                 dp[j] = dp[j - g[i]] + v[i];
//             }
//         }
//     }

//     printf("%d\n", dp[W]);
//     for (int i = 0; i < N; i++)
//     {
//         int num = 0;
//         for (int j = g[i]; j <= W; j++)
//         {
//             if (dp[j] == dp[j - g[i]] + v[i])
//             {
//                 num++;
//             }
//         }
//         if (num > 0)
//         {
//             printf("%s %d\n", name[i], num);
//         }
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

struct item
{
    char name[15];
    int weight;
    int value;
    double ratio; // value to weight ratio
};

int cmp(const void *a, const void *b)
{
    struct item *pa = (struct item *)a;
    struct item *pb = (struct item *)b;
    return pb->ratio - pa->ratio;
}

int main()
{
    int n, W;
    FILE *fp = fopen("BAG.INP", "r");
    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return 1;
    }
    fscanf(fp, "%d %d", &n, &W);
    struct item items[MAXN];
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%d %d %s", &items[i].weight, &items[i].value, items[i].name);
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    fclose(fp);
    qsort(items, n, sizeof(struct item), cmp);

    int total_weight = 0;
    int total_value = 0;
    int countarr[MAXN];
    for (int i = 0; i < n; i++)
    {
        int count = (W - total_weight) / items[i].weight;
        total_weight += count * items[i].weight;
        total_value += count * items[i].value;
        if (count > 0)
        {
            countarr[i] = count;
        }
    }
    printf("%d\n", total_value);
    for (int i = 0; i < n; i++)
    {
        if (countarr[i] > 0)
            printf("%s %d\n", items[i].name, countarr[i]);
    }
    return 0;
}
