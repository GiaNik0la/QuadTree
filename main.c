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
  
  struct Circle range = {0, 0, rand() % 100 + 100};
  struct Rect range_two = {0, 0, rand() % 100 + 100, rand() % 100 + 100};

  bool drawRect = false;
  bool drawCircle = false;
  while (!WindowShouldClose()) {
    range.x = GetMousePosition().x;
    range.y = GetMousePosition().y;
    range_two.x = GetMousePosition().x - range_two.w/2;
    range_two.y = GetMousePosition().y - range_two.h/2;

    if (IsKeyPressed(KEY_TAB)) drawRect = !drawRect;
    if (IsKeyPressed(KEY_SPACE)) drawCircle = !drawCircle;
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
      if (drawCircle) {
        DrawCircleLines(range.x, range.y, range.r, GREEN);
        list = queryCircle(qtree, range);
      } else {
        DrawRectangleLines(range_two.x, range_two.y, range_two.w, range_two.h, GREEN);
        list = query(qtree, range_two);
      }

      drawPoints(list);
    EndDrawing();
  }

  freeTree(qtree);
  freeList(list);
  return 0;
}