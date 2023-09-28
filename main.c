#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct QuadTree {
  double x, y, w, h;
  struct QuadTree *tl, *tr, *bl, *br; 
  bool isDevided;
};

struct QuadTree* createNode(double x, double y, double w, double h) {
  struct QuadTree *node = malloc(sizeof(struct QuadTree));

  node->tl = NULL;
  node->tr = NULL;
  node->bl = NULL;
  node->br = NULL;

  node->x = x;
  node->y = y;
  node->w = w;
  node->h = h;

  node->isDevided = false;

  return node;
}

void freeTree(struct QuadTree *tree) {
  if (tree->isDevided) {
    freeTree(tree->tl);
    freeTree(tree->tr);
    freeTree(tree->bl);
    freeTree(tree->br);
  }

  free(tree);
}

void subdevide(struct QuadTree *node) {
  node->tl = createNode(node->x, node->y, node->w/2, node->h/2);
  node->tr = createNode(node->x + node->w/2, node->y, node->w/2, node->h/2);
  node->bl = createNode(node->x, node->y + node->h/2, node->w/2, node->h/2);
  node->br = createNode(node->x + node->w/2, node->y + node->h/2, node->w/2, node->h/2);
  node->isDevided = true;
}

void printTree(struct QuadTree *tree) {
  printf("x: %f, y: %f, w: %f, h: %f\n", tree->x, tree->y, tree->w, tree->h);
  
  if (tree->isDevided) {
    printTree(tree->tl);
    printTree(tree->tr);
    printTree(tree->bl);
    printTree(tree->br);
  }
}

int main() {
  struct QuadTree *qtree = createNode(0, 0, 400, 400);  
  subdevide(qtree);
  printTree(qtree);

  freeTree(qtree);
  return 0;
}