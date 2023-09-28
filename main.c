#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/QuadTree.h"
#include "include/raylib.h"

int main(void) {
  const int width = 400;
  const int height = 400;

  InitWindow(width, height, "QuadTree");

//  struct QuadTree *qtree = createNode(0, 0, width, height);
//  subdevide(qtree);
//  subdevide(qtree->bl);
//  printTree(qtree);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);
      drawTree(NULL);
    EndDrawing();
  }

//  freeTree(qtree);
  return 0;
}