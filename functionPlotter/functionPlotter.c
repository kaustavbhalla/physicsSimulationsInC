#include "raylib.h"
#include <math.h>
#include <stdio.h>

int WIDTH = 1919;
int HEIGHT = 1020;

void drawGrid(int WIDTH, int HEIGHT) {
  Vector2 startHori = {(float)WIDTH / 2, 0};
  Vector2 endHori = {(float)WIDTH / 2, HEIGHT};

  Vector2 startVerti = {0, (float)HEIGHT / 2};
  Vector2 endVerti = {WIDTH, (float)HEIGHT / 2};
  float thick = 3;
  DrawLineEx(startHori, endHori, thick, WHITE);
  DrawLineEx(startVerti, endVerti, thick, WHITE);
}

void drawLighterGrid(int WIDTH, int HEIGHT) {
  float step = (float)WIDTH / 6;

  for (int i = 1; i < 6; i++) {
    float x = step * i;

    Vector2 start = {x, 0};
    Vector2 end = {x, (float)HEIGHT};

    DrawLineEx(start, end, 1, GRAY);
  }

  float horiStep = (float)HEIGHT / 6;

  for (int i = 1; i < 6; i++) {
    float y = horiStep * i;

    Vector2 start = {0, y};
    Vector2 end = {(float)WIDTH, y};

    DrawLineEx(start, end, 1, GRAY);
  }
}

void drawFunction(int WIDTH, int HEIGHT) {
  double x = 0;
  double fx;
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
    drawLighterGrid(WIDTH, HEIGHT);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
