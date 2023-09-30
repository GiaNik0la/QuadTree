#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/QuadTree.h"
#include "include/Point.h"
#include "include/raylib.h"

int main(void) {
  const int width = 800;
  const int height = 800;

  InitWindow(width, height, "QuadTree");

  struct QuadTree *qtree = createNode(0, 0, width, height, 4);

  for (int i = 0; i < 50; i++) {
    struct Point p = {i, i};
    insertPoint(qtree, p);
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(BLACK);
      drawTree(qtree);
    EndDrawing();
  }

  freeTree(qtree);
  return 0;
}