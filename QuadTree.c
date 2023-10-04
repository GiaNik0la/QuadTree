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

bool circleContains(struct Circle r, struct Point p) {
  double distX = p.x - r.x;
  double distY = p.y - r.y;
  double distSqr = distX*distX + distY*distY;
  return (distSqr < r.r*r.r);
}

struct QuadTree* createNode(double x, double y, double w, double h, int capacity) {
  struct QuadTree *node = (struct QuadTree*)malloc(sizeof(struct QuadTree));

  node->tl = NULL;
  node->tr = NULL;
  node->bl = NULL;
  node->br = NULL;

  node->bounds.x = x;
  node->bounds.y = y;
  node->bounds.w = w;
  node->bounds.h = h;

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

  node->tl = createNode(node->bounds.x, node->bounds.y, node->bounds.w/2, node->bounds.h/2, node->capacity);
  node->tr = createNode(node->bounds.x + node->bounds.w/2, node->bounds.y, node->bounds.w/2, node->bounds.h/2, node->capacity);
  node->bl = createNode(node->bounds.x, node->bounds.y + node->bounds.h/2, node->bounds.w/2, node->bounds.h/2, node->capacity);
  node->br = createNode(node->bounds.x + node->bounds.w/2, node->bounds.y + node->bounds.h/2, node->bounds.w/2, node->bounds.h/2, node->capacity);
  node->isDevided = true;
}

void printTree(struct QuadTree *tree) {
  printf("x: %f, y: %f, w: %f, h: %f\n", tree->bounds.x, tree->bounds.y, tree->bounds.w, tree->bounds.h);
  printList(tree->points);
  
  if (tree->isDevided) {
    printTree(tree->tl);
    printTree(tree->tr);
    printTree(tree->bl);
    printTree(tree->br);
  }
}

void drawTree(struct QuadTree *tree, bool drawRect) {
  if (drawRect) DrawRectangleLines(tree->bounds.x, tree->bounds.y, tree->bounds.w, tree->bounds.h, RAYWHITE);

  if (tree->isDevided) {
    drawTree(tree->tl, drawRect);
    drawTree(tree->tr, drawRect);
    drawTree(tree->bl, drawRect);
    drawTree(tree->br, drawRect);
  }

  struct node *tmp = tree->points;
  while (tmp) {
    DrawCircle(tmp->val.x, tmp->val.y, 3, RAYWHITE);
    tmp = tmp->next;
  }
}

void insertPoint(struct QuadTree *tree, struct Point p) {
  if (!rectContains(tree->bounds, p)) return;

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

bool intersects(struct Rect range_one, struct Rect range_two) {
  return !(range_two.x > range_one.x + range_one.w ||
           range_two.x + range_two.w < range_one.x ||
           range_two.y > range_one.y + range_one.h ||
           range_two.y + range_two.h < range_one.y );
}

bool circleIntersects(struct Circle range_one, struct Rect range_two) {
  double cdx = abs(range_one.x - (range_two.x + range_two.w/2));
  double cdy = abs(range_one.y - (range_two.y + range_two.h/2));

  if (cdx > (range_two.w/2 + range_one.r)) return false;
  if (cdy > (range_two.h/2 + range_one.r)) return false;

  if (cdx <= range_two.w/2) return true;
  if (cdy <= range_two.h/2) return true;

  double cornerDistSq = (cdx - range_two.w/2)*(cdx - range_two.w/2) +
                        (cdy - range_two.h/2)*(cdy - range_two.h/2);

  return (cornerDistSq <= range_one.r*range_one.r);
}

struct node* query(struct QuadTree *tree, struct Rect range) {
  struct node* pointsInRange = NULL;
  if (!intersects(tree->bounds, range)) return pointsInRange;

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

struct node* queryCircle(struct QuadTree *tree, struct Circle range) {
  struct node* pointsInRange = NULL;
  if (!circleIntersects(range, tree->bounds)) return pointsInRange;

  struct node *tmp = tree->points;
  while (tmp) {
    if (circleContains(range, tmp->val)) {
      insertLast(&pointsInRange, tmp->val);
    }
    tmp = tmp->next;
  }

  if (tree->isDevided) {
    concat(&pointsInRange, queryCircle(tree->tl, range));
    concat(&pointsInRange, queryCircle(tree->tr, range));
    concat(&pointsInRange, queryCircle(tree->bl, range));
    concat(&pointsInRange, queryCircle(tree->br, range));
  }

  return pointsInRange;
}