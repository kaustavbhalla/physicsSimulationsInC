#include "raylib.h"
#include <math.h>
#include <stdio.h>

int HEIGHT = 1080;
int WIDTH = 1920;

int main() {
  printf("Wow, this is working!\n");

  InitWindow(WIDTH, HEIGHT, "Projectile Motion");

  while (!WindowShouldClose()) {
    WIDTH = GetScreenWidth();
    HEIGHT = GetScreenHeight();

    Vector2 positionStart = {0, HEIGHT - 225};
    Vector2 positionEnd = {WIDTH, HEIGHT - 225};
    Color color = LIGHTGRAY;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawLineEx(positionStart, positionEnd, 3, color);

    double theta = 45 * DEG2RAD;
    double g = 9.84;
    double u = 120;
    float groundY = HEIGHT - 255;

    for (int xPos = 10; xPos < WIDTH; xPos++) {

      double x = xPos;
      double y = ((x)*tan(theta)) -
                 (g * x * x) / (2 * u * u * cos(theta) * cos(theta));

      Vector2 position = {x, groundY - y};

      DrawPixelV(position, WHITE);
    }
    DrawText("Projectile", WIDTH / 4, 50, 20, GREEN);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
