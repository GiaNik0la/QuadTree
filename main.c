#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "include/QuadTree.h"
#include "include/Point.h"
#include "include/raylib.h"

int main(void) {
  const int width = 800;
  const int height = 800;

  InitWindow(width, height, "QuadTree");

  struct QuadTree *qtree = createNode(0, 0, width, height, 4);

  for (int i = 0; i < 500; i++) {
    struct Point p;
    p.x = rand() % (width - 1) + 1;
    p.y = rand() % (height - 1) + 1;
    insertPoint(qtree, p);
  }

  struct node *list = NULL;

  while (!WindowShouldClose()) {

    struct Rect range = {GetMousePosition().x, GetMousePosition().y, 107, 72};

    BeginDrawing();
      ClearBackground(BLACK);
      drawTree(qtree);
      DrawRectangleLines(range.x, range.y, range.w, range.h, GREEN);
      list = query(qtree, range);
      drawPoints(list);
    EndDrawing();
  }

  freeTree(qtree);
  freeList(list);
  return 0;
}