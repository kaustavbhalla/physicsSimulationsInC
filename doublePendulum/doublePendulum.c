#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600

void drawPendulum(float theta1, int length) {
  Vector2 upperStart = {(float)WIDTH / 4, (float)HEIGHT / 4};
  Vector2 upperEnd = {(float)WIDTH / 2, (float)HEIGHT / 4};

  DrawLineV(upperStart, upperEnd, LIGHTGRAY);

  Vector2 stringStart;
  stringStart.x = (upperStart.x + upperEnd.x) / 2;
  stringStart.y = upperStart.y;

  Vector2 stringEnd;
  stringEnd.x = stringStart.x + (length * sin(theta1));
  stringEnd.y = stringStart.y + (length * cos(theta1));

  DrawLineV(stringStart, stringEnd, GREEN);

  int gap = 30;
  Vector2 circleCenter;
  circleCenter.x = stringStart.x + ((length + gap) * sin(theta1));
  circleCenter.y = stringStart.y + ((length + gap) * cos(theta1));

  DrawCircleV(circleCenter, gap, RED);
}

int main() {
  InitWindow(WIDTH, HEIGHT, "Double Pendulum");

  SetTargetFPS(60);

  // constants

  float theta = 1.0467f;
  float angularAcc = 0.0f;
  float angularVel = 0.0f;

  float gravity = 9.81f;
  float lengthForMath = 1.5f;

  while (!WindowShouldClose()) {

    float dt = GetFrameTime();

    angularAcc = (-gravity / lengthForMath) * sin(theta);
    angularVel += angularAcc * dt;

    theta += angularVel * dt;
    BeginDrawing();
    ClearBackground(BLACK);
    drawPendulum(theta, 150);
    EndDrawing();
  }

  return 0;
}
