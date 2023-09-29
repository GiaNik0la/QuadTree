#ifndef POINT
#define POINT

struct Point {
  int x, y;
};

struct node {
  struct Point val;
  struct node *next;
};

struct node* end(struct node *head);
int getSize(struct node *head);
void insert(struct node **n, struct Point p);
void insertFirst(struct node **head, struct Point p);
void insertLast(struct node **head, struct Point p);
void deleteFirst(struct node **head);
void deleteLast(struct node **head);
void printList(struct node *head);
void freeList(struct node *head);

#endif