#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "QuadTree.h"

int main() {
  struct QuadTree *qtree = createNode(0, 0, 400, 400);
  subdevide(qtree);
  subdevide(qtree->bl);
  printTree(qtree);

  freeTree(qtree);
  return 0;
}