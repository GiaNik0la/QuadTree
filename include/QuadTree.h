#ifndef QUAD_TREE
#define QUAD_TREE

#include "Point.h"

struct QuadTree {
  double x, y, w, h;
  int capacity;
  struct QuadTree *tl, *tr, *bl, *br; 
  struct node *points;
  bool isDevided;
};

struct QuadTree* createNode(double x, double y, double w, double h, int capacity); 
void freeTree(struct QuadTree *tree);
void subdevide(struct QuadTree *node);
void printTree(struct QuadTree *tree);
void drawTree(struct QuadTree *tree);
void insertPoint(struct QuadTree *tree, struct Point p);

#endif