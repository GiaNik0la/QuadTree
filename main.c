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

  while (!WindowShouldClose()) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      struct Point p = {round(GetMousePosition().x), round(GetMousePosition().y)};
      insertPoint(qtree, p);
    }

    BeginDrawing();
      ClearBackground(BLACK);
      drawTree(qtree);
    EndDrawing();
  }

  freeTree(qtree);
  return 0;
}