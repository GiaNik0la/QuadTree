#ifndef QUAD_TREE
#define QUAD_TREE
#include <stdbool.h>

struct QuadTree {
  double x, y, w, h;
  struct QuadTree *tl, *tr, *bl, *br; 
  bool isDevided;
};

struct QuadTree* createNode(double x, double y, double w, double h); 
void freeTree(struct QuadTree *tree);
void subdevide(struct QuadTree *node);
void printTree(struct QuadTree *tree);

#endif