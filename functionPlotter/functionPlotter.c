#include "raylib.h"
#include <stdio.h>

int WIDTH = 1919;
int HEIGHT = 1020;

void drawGrid(int WIDTH, int HEIGHT) {
  Vector2 start = {(float)WIDTH / 2, 0};
  Vector2 end = {(float)WIDTH / 2, HEIGHT};
  float thick = 2;
  DrawLineEx(start, end, thick, WHITE);
}

int main() {
  printf("Function plotter in C");

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH, HEIGHT, "Function Plotter");

  while (!WindowShouldClose()) {
    int WIDTH = GetScreenWidth();
    int HEIGHT = GetScreenHeight();

    BeginDrawing();

    ClearBackground(BLACK);
    const char *text = "Function Plotter In C";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    int midWidTex = (WIDTH - textWidth) / 2;
    int midHigTex = (HEIGHT - fontSize) / 2;

    DrawText("Function Plotter in C", midWidTex, midHigTex / 4, fontSize,
             GREEN);

    drawGrid(WIDTH, HEIGHT);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
