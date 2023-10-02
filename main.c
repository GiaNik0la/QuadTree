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

  for (int i = 0; i < 1000; i++) {
    struct Point p;
    p.x = rand() % (width - 1) + 1;
    p.y = rand() % (height - 1) + 1;
    insertPoint(qtree, p);
  }

  struct node *list = NULL;
  
  struct Rect range = {0, 0, rand() % 100 + 100, rand() % 100 + 100};

  bool drawRect = false;
  while (!WindowShouldClose()) {
    range.x = GetMousePosition().x - range.w/2;
    range.y = GetMousePosition().y - range.h/2;

    if (IsKeyPressed(KEY_TAB)) drawRect = !drawRect;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      struct Point p;
      p.x = GetMousePosition().x + rand() % 20 - 10;
      p.y = GetMousePosition().y + rand() % 20 - 10;
      insertPoint(qtree, p);
    }

    BeginDrawing();
      struct Color c = {10, 10, 10, 255};
      ClearBackground(c);
      drawTree(qtree, drawRect);
      DrawRectangleLines(range.x, range.y, range.w, range.h, GREEN);
      list = query(qtree, range);
      drawPoints(list);
    EndDrawing();
  }

  freeTree(qtree);
  freeList(list);
  return 0;
}