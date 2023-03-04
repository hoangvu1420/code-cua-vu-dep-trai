#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_LENGTH 10
#define MAX_LENGTH 500
#define MIN_WIDTH 3
#define MAX_WIDTH 20

typedef struct node
{
  int so_dong;
  int area;
  char giao_lo1[255];
  char giao_lo2[255];
  char ten_duong[255];
  int length;
  int width;
  int chieu;
  int height;
  struct node *left;
  struct node *right;
} Node_t;

Node_t *root = NULL;

Node_t *new_node(int so_dong, char giao_lo1[5], char giao_lo2[5], char ten_duong[4], int length, int width, int chieu)
{
  Node_t *new_node = (Node_t *)malloc(sizeof(Node_t));
  new_node->so_dong = so_dong;
  new_node->area = length * width;
  strcpy(new_node->giao_lo1, giao_lo1);
  strcpy(new_node->giao_lo2, giao_lo2);
  strcpy(new_node->ten_duong, ten_duong);
  new_node->length = length;
  new_node->width = width;
  new_node->chieu = chieu;
  new_node->right = NULL;
  return new_node;
}

int calculateTotalIndex(char *intersection)
{
  int index = 0;
  for (int i = 1; i <= 3; i++)
  {
    index += (intersection[i] - '0') * (1 << (4 - i));
  }
  return index;
}

int compareNodes(Node_t *a, Node_t *b)
{
  int cmp = strcmp(a->ten_duong, b->ten_duong);
  if (cmp == 0)
  {
    int totalIndexA = calculateTotalIndex(a->giao_lo1) + calculateTotalIndex(a->giao_lo2);
    int totalIndexB = calculateTotalIndex(b->giao_lo1) + calculateTotalIndex(b->giao_lo2);
    if (totalIndexA == totalIndexB)
    {
      a->length += b->length;
      a->width = (a->width < b->width) ? a->width : b->width;
      return 0;
    }
    else
    {
      return (totalIndexA > totalIndexB) ? 1 : -1;
    }
  }
  else
  {
    return cmp;
  }
}

Node_t *insert(Node_t *root, Node_t *node)
{
  if (root == NULL)
  {
    return node;
  }
  int cmp = compareNodes(node, root);
  if (cmp < 0)
  {
    root->left = insert(root->left, node);
  }
  else if (cmp > 0)
  {
    root->right = insert(root->right, node);
  }
  return root;
}

int check_giao_lo(char giao_lo[5])
{
  if (strlen(giao_lo) != 4)
  {
    return 0;
  }
  if (giao_lo[0] != 'J')
  {
    return 0;
  }
  for (int i = 1; i < 4; i++)
  {
    if (giao_lo[i] < '0' || giao_lo[i] > '9')
    {
      return 0;
    }
  }
  return 1;
}

int check_length_width(int length, int width)
{
  if (length < MIN_LENGTH || length > MAX_LENGTH)
  {
    return 0;
  }
  if (width < MIN_WIDTH || width > MAX_WIDTH)
  {
    return 0;
  }
  return 1;
}
  char f_in_ten_duong[20];

Node_t *buildTree(int N)
{
  char fileten_duong[256];
  FILE *fp = fopen(f_in_ten_duong, "r");
  if (fp == NULL)
  {
    printf("Error: Failed to open file %s\n", fileten_duong);
    exit(1);
  }
  int Lines;
  fscanf(fp, "%d", &Lines);
  Node_t *root = NULL;
  int count = 0;
  for (int i = 0; i < N; i++)
  {
    char giao_lo1[5], giao_lo2[5], ten_duong[4];
    int length, width, directions;
    fscanf(fp, "%4s %4s %3s %d %d %d", giao_lo1, giao_lo2, ten_duong, &length, &width, &directions);
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));

    strcpy(node->giao_lo1, giao_lo1);
    strcpy(node->giao_lo2, giao_lo2);
    strcpy(node->ten_duong, ten_duong);
    node->length = length;
    node->width = width;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    if (check_giao_lo(giao_lo1) && check_giao_lo(giao_lo2) && check_length_width(length, width))
      root = insert(root, node);
      count++;
  }
  printf("So node: %d\n", count);
  fclose(fp);
  return root;
}

int height(Node_t *root)
{
  if (root == NULL)
  {
    return -1;
  }

  int leftHeight = height(root->left);
  int rightHeight = height(root->right);

  if (leftHeight > rightHeight)
  {
    return leftHeight + 1;
  }
  else
  {
    return rightHeight + 1;
  }
}
int main()
{
  printf("Hay nhap ten file input dau vao: ");
  scanf("%s", &f_in_ten_duong);
  FILE *fp = fopen(f_in_ten_duong, "r");
  if (fp == NULL)
  {
    printf("Error opening file\n");
    return 1;
  }
  int num_lines;
  fscanf(fp, "%d", &num_lines);

  int so_dong = 1;
  char giao_lo1[5];
  char giao_lo2[5];
  char ten_duong[4];
  int length;
  int width;
  int chieu;

  int count_giao_lo = 0;
  int count_duong = 0;

  int max_area_so_dong = 0;
  int max_area = 0;

  while (fscanf(fp, "%s %s %s %d %d %d", giao_lo1, giao_lo2, ten_duong, &length, &width, &chieu) == 6)
  {
    if (check_giao_lo(giao_lo1) && check_giao_lo(giao_lo2))
      count_giao_lo++;
    if (check_length_width(length, width))
      count_duong++;
    if(length * width > max_area && check_giao_lo(giao_lo1) && check_giao_lo(giao_lo2) && check_length_width(length, width))
    {
      max_area = length * width;
      max_area_so_dong = so_dong;
    }
    so_dong++;
  }
  rewind(fp);
  fclose(fp);

  printf("%d\n", count_giao_lo);
  printf("%d\n", count_duong);
  printf("%d\n", max_area_so_dong);
  int n;
  printf("Nhap vao N: ");
  scanf("%d", &n);

  root = buildTree(n);
  printf("%d", height(root));

  return 0;
}