#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/QuadTree.h"
#include "include/Point.h"
#include "include/raylib.h"

bool rectContains(struct Rect r, struct Point p) {
  return !(p.x < r.x ||
           p.x > r.x + r.w ||
           p.y < r.y ||
           p.y > r.y + r.h);
}

struct QuadTree* createNode(double x, double y, double w, double h, int capacity) {
  struct QuadTree *node = (struct QuadTree*)malloc(sizeof(struct QuadTree));

  node->tl = NULL;
  node->tr = NULL;
  node->bl = NULL;
  node->br = NULL;

  node->x = x;
  node->y = y;
  node->w = w;
  node->h = h;

  node->capacity = capacity;

  node->isDevided = false;

  node->points = NULL;

  return node;
}

void freeTree(struct QuadTree *tree) {
  if (tree->isDevided) {
    freeTree(tree->tl);
    freeTree(tree->tr);
    freeTree(tree->bl);
    freeTree(tree->br);
  }

  freeList(tree->points);
  free(tree);
}

void subdevide(struct QuadTree *node) {
  if (node->isDevided)
    return;

  node->tl = createNode(node->x, node->y, node->w/2, node->h/2, node->capacity);
  node->tr = createNode(node->x + node->w/2, node->y, node->w/2, node->h/2, node->capacity);
  node->bl = createNode(node->x, node->y + node->h/2, node->w/2, node->h/2, node->capacity);
  node->br = createNode(node->x + node->w/2, node->y + node->h/2, node->w/2, node->h/2, node->capacity);
  node->isDevided = true;
}

void printTree(struct QuadTree *tree) {
  printf("x: %f, y: %f, w: %f, h: %f\n", tree->x, tree->y, tree->w, tree->h);
  printList(tree->points);
  
  if (tree->isDevided) {
    printTree(tree->tl);
    printTree(tree->tr);
    printTree(tree->bl);
    printTree(tree->br);
  }
}

void drawTree(struct QuadTree *tree, bool drawRect) {
  if (drawRect) DrawRectangleLines(tree->x, tree->y, tree->w, tree->h, RAYWHITE);

  if (tree->isDevided) {
    drawTree(tree->tl, drawRect);
    drawTree(tree->tr, drawRect);
    drawTree(tree->bl, drawRect);
    drawTree(tree->br, drawRect);
  }

  struct node *tmp = tree->points;
  while (tmp) {
    DrawCircle(tmp->val.x, tmp->val.y, 2, RAYWHITE);
    tmp = tmp->next;
  }
}

void insertPoint(struct QuadTree *tree, struct Point p) {
  bool conatins = p.x < tree->x + tree->w &&
                  p.x > tree->x &&
                  p.y < tree->y + tree->h &&
                  p.y > tree->y;

  if (!conatins) return;

  if (getSize(tree->points) < tree->capacity) {
    insertLast(&tree->points, p);
  } else {
    subdevide(tree);

    insertPoint(tree->tl, p);
    insertPoint(tree->tr, p);
    insertPoint(tree->bl, p);
    insertPoint(tree->br, p);
  }
}

bool intersects(struct QuadTree *tree, struct Rect range) {
  return !(range.x > tree->x + tree->w ||
           range.x + range.w < tree->x ||
           range.y > tree->y + tree->h ||
           range.y + range.h < tree->y );
}

struct node* query(struct QuadTree *tree, struct Rect range) {
  struct node* pointsInRange = NULL;
  if (!intersects(tree, range)) return pointsInRange;

  struct node *tmp = tree->points;
  while (tmp) {
    if (rectContains(range, tmp->val)) {
      insertLast(&pointsInRange, tmp->val);
    }
    tmp = tmp->next;
  }

  if (tree->isDevided) {
    concat(&pointsInRange, query(tree->tl, range));
    concat(&pointsInRange, query(tree->tr, range));
    concat(&pointsInRange, query(tree->bl, range));
    concat(&pointsInRange, query(tree->br, range));
  }

  return pointsInRange;
}