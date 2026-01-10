#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define THICK 5
#define MASS_WIDTH 100

#define FPS 60

void floorDraw(int HEIGHT, int WIDTH) {
  Vector2 start = {0, HEIGHT * 0.6};
  Vector2 end = {WIDTH, HEIGHT * 0.6};
  DrawLineEx(start, end, THICK, GRAY);
}

void massDraw(int HEIGHT, int WIDTH, double x) {
  Rectangle rect = {x, (HEIGHT * 0.6) - MASS_WIDTH - (float)THICK / 2,
                    MASS_WIDTH, MASS_WIDTH};
  DrawRectangleRec(rect, RED);
}

int main() {
  printf("Wow, is this working?\n");
  int HEIGHT = 600;
  int WIDTH = 900;
  int amplitude = 10;
  int freq = 5;
  double phi = 0;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH, HEIGHT, "Spring Mass System Simulator");

  double x = ((double)WIDTH / 2) - ((double)MASS_WIDTH / 2);
  float dt;
  float v = 20;
  // SetTargetFPS(FPS);

  // Start drawing loop
  while (!WindowShouldClose()) {
    int WIDTH = GetScreenWidth();
    int HEIGHT = GetScreenHeight();

    BeginDrawing();

    ClearBackground(BLACK);
    floorDraw(HEIGHT, WIDTH);

    dt = GetFrameTime();
    x += v * dt;
    massDraw(HEIGHT, WIDTH, x);
    DrawFPS(10, 10);

    DrawText("Spring Mass system simulator goes here!", WIDTH / 10, 100, 30,
             GREEN);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
