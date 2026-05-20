#include "raylib.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define TRAIL_LENGTH 150

void drawPendulum(float theta1, float theta2, int length, int length2) {
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

  // secondPendulum
  Vector2 secondPstrt;
  secondPstrt.x = circleCenter.x + (gap * sin(theta2));
  secondPstrt.y = circleCenter.y + (gap * cos(theta2));

  Vector2 secondPend;
  secondPend.x = circleCenter.x + ((gap + length2) * sin(theta2));
  secondPend.y = circleCenter.y + ((gap + length2) * cos(theta2));

  DrawLineV(secondPstrt, secondPend, RED);

  Vector2 circleCenter2;
  int gap2 = 30;
  circleCenter2.x = circleCenter.x + ((gap + gap2 + length2) * sin(theta2));
  circleCenter2.y = circleCenter.y + ((gap + gap2 + length2) * cos(theta2));

  DrawCircleV(circleCenter2, gap2, RED);
}

int main() {
  printf("Welcome to double pendulum");
  InitWindow(WIDTH, HEIGHT, "Double Pendulum");

  SetTargetFPS(60);

  // constants

  float theta1 = 1.57f;
  float theta2 = 1.57f;
  float theta1AngV = 1.0f;
  float theta2AngV = 1.0f;

  float gravity = 9.81f;
  float lengthForMath = 1.5f;

  float length2 = 2.0f;

  float m1 = 100.0f;
  float m2 = 100.0f;

  bool isDragging1 = false;
  bool isDragging2 = false;

  Vector2 trail[TRAIL_LENGTH] = {0};
  while (!WindowShouldClose()) {

    float dt = GetFrameTime();
    // theta1 ang angularAcc

    Vector2 pivot = {((float)WIDTH / 4 + (float)WIDTH / 2) / 2,
                     (float)HEIGHT / 4};

    Vector2 bob1 = {pivot.x + (180 * sin(theta1)),
                    pivot.y + (180 * cos(theta1))};
    Vector2 bob2 = {bob1.x + (260 * sin(theta2)), bob1.y + (260 * cos(theta2))};

    Vector2 mousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      if (CheckCollisionPointCircle(mousePos, bob2, 30)) {
        isDragging2 = true;
      } else if (CheckCollisionPointCircle(mousePos, bob1, 30)) {
        isDragging1 = true;
      }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      isDragging1 = false;
      isDragging2 = false;
    }

    if (isDragging1) {
      theta1 = atan2f(mousePos.x - pivot.x, mousePos.y - pivot.y);
      theta1AngV = 0.0f;
      theta2AngV = 0.0f;
    } else if (isDragging2) {
      theta2 = atan2f(mousePos.x - bob1.x, mousePos.y - bob1.y);
      theta1AngV = 0.0f;
      theta2AngV = 0.0f;
    } else {
      double p1 = (-gravity) * (2 * m1 + m2) * sin(theta1);
      double p2 = m2 * gravity * sin(theta1 - (2 * theta2));
      double p3 =
          2 * sin(theta1 - theta2) * m2 *
          ((theta2AngV * theta2AngV * length2) +
           (theta1AngV * theta1AngV * lengthForMath * cos(theta1 - theta2)));

      double d1 =
          lengthForMath * ((2 * m1) + m2 - m2 * cos(2 * theta1 - 2 * theta2));

      double theta1AngA = (p1 - p2 - p3) / d1;

      // theta2 ang angularAcc

      double pP1 =
          2 * sin(theta1 - theta2) *
          (theta1AngV * theta1AngV * lengthForMath * (m1 + m2) +
           (gravity * (m1 + m2)) * cos(theta1) +
           (theta2AngV * theta2AngV * length2 * m2 * cos(theta1 - theta2)));
      double pP2 =
          length2 * ((2 * m1) + m2 - (m2 * cos((2 * theta1) - (2 * theta2))));

      double theta2AngA = pP1 / pP2;
      // angularVel += angularAcc * dt;

      theta1AngV += theta1AngA * dt;
      theta2AngV += theta2AngA * dt;
      // theta += angularVel * dt

      theta1 += theta1AngV * dt;
      theta2 += theta2AngV * dt;
      Vector2 bob2 = {bob1.x + (260 * sin(theta2)),
                      bob1.y + (260 * cos(theta2))};

      for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
        trail[i] = trail[i - 1];
      }

      trail[0] = bob2;
    }
    BeginDrawing();
    ClearBackground(BLACK);

    for (int i = 0; i < TRAIL_LENGTH - 1; i++) {
      if (trail[i].x != 0 && trail[i + 1].x != 0) {
        float alpha = 1.0f - ((float)i / TRAIL_LENGTH);
        Color trailColor = Fade(SKYBLUE, alpha);

        DrawLineEx(trail[i], trail[i + 1], 3.0f, trailColor);
      }
    }
    drawPendulum(theta1, theta2, 150, 200);
    EndDrawing();
  }

  return 0;
}
