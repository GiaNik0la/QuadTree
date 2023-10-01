# QuadTree
I made quad tree in C. if you move your mouse around, a rectangle will follow and highlight every point within it and it does this with quad tree.

![Game](giphy.gif) [](giphy.gif)

# Basic idea on how this works
### What is a QuadTree
QuadTree is basically just a big rectangle which can devide into 4 rectangles if it contains too much objects. for example: say the capacity of the QuadTree is 4. and it already contains 3 points. if I add another point the tree will devide into 4.

### How the rectangle finds points within
The program only checks the parts that rectangle is overlaping. this reduces the amount of points to check

# Requirements

### You need to install:
- Raylib: https://www.raylib.com/

# How to run

type in this command:
</br>
```
gcc main.c QuadTree.c Point.c -o out -O1 -Wall -std=c99 -Wno-missing-braces -I .\include\ -L .\lib\ -lraylib -lopengl32 -lgdi32 -lwinmm
./out
```

# Controls

- to reveal the quad tree you press <kbd>Tab</kbd>
- to spawn points click <kbd>LMB</kbd> (you cannot just hold it you need to click)
