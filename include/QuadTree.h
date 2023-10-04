#ifndef QUAD_TREE
#define QUAD_TREE

#include "Point.h"

struct Circle {
  double x, y, r;
};

struct Rect {
  double x, y, w, h;
};

bool circleIntersects(struct Circle range_one, struct Rect range_two);
bool circleContains(struct Circle r, struct Point p);
bool intersects(struct Rect range_one, struct Rect range_two);
bool rectContains(struct Rect r, struct Point p);

struct QuadTree {
  struct Rect bounds;
  int capacity;
  struct QuadTree *tl, *tr, *bl, *br; 
  struct node *points;
  bool isDevided;
};

struct QuadTree* createNode(double x, double y, double w, double h, int capacity); 
void freeTree(struct QuadTree *tree);
void subdevide(struct QuadTree *node);
void printTree(struct QuadTree *tree);
void drawTree(struct QuadTree *tree, bool drawRect);
void insertPoint(struct QuadTree *tree, struct Point p);
struct node* query(struct QuadTree *tree, struct Rect range);
struct node* queryCircle(struct QuadTree *tree, struct Circle range);

#endif