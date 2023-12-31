#include <stdio.h>
#include <stdlib.h>
#include "include/Point.h"
#include "include/raylib.h"

struct node* end(struct node *head) {
  if (head == NULL) return NULL;

  struct node *result = head;
  while (result->next) result = result->next;
  return result;
}

int getSize(struct node *head) {
  struct node *tmp = head;
  int count = 0;
  while (tmp) {
    ++count;
    tmp = tmp->next;
  }
  return count;
}

void insert(struct node **n, struct Point p) {
  struct node *new = (struct node*)malloc(sizeof(struct node));
  new->next = (*n)->next;
  new->val = p;
  (*n)->next = new;
}

void insertFirst(struct node **head, struct Point p) {
  struct node *new = (struct node*)malloc(sizeof(struct node));
  new->val = p;
  new->next = (*head);
  (*head) = new;
}

void insertLast(struct node **head, struct Point p) {
  struct node *temp = end(*head);
  if (temp) {
    insert(&temp, p);  
  } else {
    insertFirst(head, p);
  }
}

void deleteFirst(struct node **head) {
  struct node *tmp = *head;
  (*head) = (*head)->next;
  free(tmp);
}

void deleteLast(struct node **head) {
  struct node *tmp = end(*head);
  struct node *prev = *head;
  while (prev->next->next) {
    prev = prev->next;
  } 
  prev->next = NULL;
  free(tmp);
}

void concat(struct node **head_one, struct node *head_two) {
  struct node *endd = end(*head_one);
  if (endd) {
    endd->next = head_two;
  } else {
    *(head_one) = head_two;
  }
}

void printList(struct node *head) {
  struct node *tmp = head;
  while (tmp) {
    printf("(x: %f, y: %f) ----> ", tmp->val.x, tmp->val.y);
    tmp = tmp->next;
  }
  printf("\n");
}

void drawPoints(struct node *head) {
  struct node *tmp = head;
  while (tmp) {
    DrawCircle(tmp->val.x, tmp->val.y, tmp->val.r, GREEN);
    tmp = tmp->next;
  }
}

void freeList(struct node *head) {
  while (head) {
    struct node *temp = head;
    head = head->next;
    free(temp);
  }
}
