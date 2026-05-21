#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define WIDTH 900
#define HEIGHT 600
#define TRAIL_LENGTH 150

void drawPendulum(float theta1, float theta2, int length, int length2) {
  float currW = (float)GetScreenWidth();
  float currH = (float)GetScreenHeight();

  Vector2 upperStart = {currW / 2 - 100.0, currH / 4};
  Vector2 upperEnd = {currW / 2 + 100.0, currH / 4};

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

  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

  InitWindow(WIDTH, HEIGHT, "Double Pendulum");

  // SetTargetFPS(120);

  // constants

  float theta1 = 1.57f;
  float theta2 = 1.57f;
  float theta1AngV = 1.0f;
  float theta2AngV = 1.0f;

  float L1 = 180.0f;
  float L2 = 260.0f;
  float m1 = 100.0f;
  float m2 = 100.0f;
  float gravity = 9.81f;

  bool isDragging1 = false;
  bool isDragging2 = false;

  Vector2 trail[TRAIL_LENGTH] = {0};

  float accumulator = 0.0f;
  float timeStep = 0.016f;

  GuiSetStyle(DEFAULT, TEXT_SIZE, 16);
  while (!WindowShouldClose()) {

    float dt = GetFrameTime();
    if (dt > 0.25f) {
      dt = 0.25f;
    }
    accumulator += dt;
    // theta1 ang angularAcc

    Vector2 pivot = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 4};

    Vector2 bob1 = {pivot.x + ((L1 + 30.0f) * sin(theta1)),
                    pivot.y + ((L1 + 30.0f) * cos(theta1))};
    Vector2 bob2 = {bob1.x + ((L2 + 30.0f) * sin(theta2)),
                    bob1.y + ((L2 + 30.0f) * cos(theta2))};

    Vector2 mousePos = GetMousePosition();

    bool isMouseOverUI = (mousePos.x < 300 && mousePos.y < 250);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !isMouseOverUI) {
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
    while (accumulator >= timeStep) {
      if (isDragging1) {
        theta1 = atan2f(mousePos.x - pivot.x, mousePos.y - pivot.y);
        theta1AngV = 0.0f;
        theta2AngV = 0.0f;
      } else if (isDragging2) {
        theta2 = atan2f(mousePos.x - bob1.x, mousePos.y - bob1.y);
        theta1AngV = 0.0f;
        theta2AngV = 0.0f;
      } else {
        double lengthForMath = L1 / 100.0;
        double length2 = L2 / 100.0;
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

        theta1AngV += theta1AngA * timeStep;
        theta2AngV += theta2AngA * timeStep;
        // theta += angularVel * dt

        theta1 += theta1AngV * timeStep;
        theta2 += theta2AngV * timeStep;
        Vector2 updatedBob1 = {pivot.x + ((L1 + 30.0f) * sin(theta1)),
                               pivot.y + ((L1 + 30.0f) * cos(theta1))};

        Vector2 updatedBob2 = {updatedBob1.x + ((L2 + 60.0f) * sin(theta2)),
                               updatedBob1.y + ((L2 + 60.0f) * cos(theta2))};

        for (int i = TRAIL_LENGTH - 1; i > 0; i--) {
          trail[i] = trail[i - 1];
        }

        trail[0] = updatedBob2;
      }
      accumulator -= timeStep;
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
    drawPendulum(theta1, theta2, L1, L2);

    // GUI Controls
    //

    DrawRectangle(10, 10, 250, 220, Fade(DARKGRAY, 0.8f));
    DrawText("PHYSICS CONTROLS", 30, 20, 20, WHITE);

    // Sliders: (Bounds, Text Left, Text Right, Variable Pointer, Min Value, Max
    // Value)
    GuiSlider((Rectangle){60, 60, 140, 20}, "L1", TextFormat("%.0f", L1), &L1,
              50.0f, 400.0f);
    GuiSlider((Rectangle){60, 90, 140, 20}, "L2", TextFormat("%.0f", L2), &L2,
              50.0f, 400.0f);
    GuiSlider((Rectangle){60, 120, 140, 20}, "M1", TextFormat("%.0f", m1), &m1,
              10.0f, 500.0f);
    GuiSlider((Rectangle){60, 150, 140, 20}, "M2", TextFormat("%.0f", m2), &m2,
              10.0f, 500.0f);
    GuiSlider((Rectangle){60, 180, 140, 20}, "Grav",
              TextFormat("%.1f", gravity), &gravity, 0.0f, 50.0f);
    EndDrawing();
  }

  return 0;
}
