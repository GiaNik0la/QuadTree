#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/QuadTree.h"
#include "include/Point.h"
#include "include/raylib.h"

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

void drawTree(struct QuadTree *tree) {
  DrawRectangleLines(tree->x, tree->y, tree->w, tree->h, RAYWHITE);

  if (tree->isDevided) {
    drawTree(tree->tl);
    drawTree(tree->tr);
    drawTree(tree->bl);
    drawTree(tree->br);
  }
}

void insertPoint(struct QuadTree *tree, struct Point p) {
  if (getSize(tree->points) < tree->capacity) {
    if (p.x < tree->w && p.x > tree->x &&
        p.y < tree->h && p.y > tree->y)
      insertLast(&tree->points, p);
  } else {
    subdevide(tree);

    insertPoint(tree->tl, p);
    insertPoint(tree->tr, p);
    insertPoint(tree->bl, p);
    insertPoint(tree->br, p);
  }
}