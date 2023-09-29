#include <stdio.h>
#include <stdlib.h>
#include "include/Point.h"

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
    tmp = tmp->next;
    count++;
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
  new->next = (*head);
  new->val = p;
  (*head) = new;
}

void insertLast(struct node **head, struct Point p) {
  struct node *temp = end(*head);
  if (temp) {
    while (temp->next) temp = temp->next;
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

void freeList(struct node *head) {
  struct node *temp;
 
  while (head) {
    temp = head;
    head = head->next;
    free(temp);
  }
}
