#include "raylib.h"
#include <math.h>
#include <stdio.h>

#define THICK 5
#define MASS_WIDTH 100
#define FPS 240
#define NUM_SPRING_ELEMENTS 16
#define SPRING_ELEM_LENGTH 60
#define K 10
#define FRICTION 10

float v = 80;
float a = 2;

typedef struct {
  Vector2 start, end;
} SpringEl;

SpringEl springElements[NUM_SPRING_ELEMENTS];

void springDraw(int HEIGHT, int WIDTH, float x_mass) {
  float x_springdelta = x_mass / NUM_SPRING_ELEMENTS;
  float y_end = sqrt(pow(SPRING_ELEM_LENGTH, 2) - pow(x_springdelta, 2));

  for (int i = 0; i < NUM_SPRING_ELEMENTS; i += 2) {
    Vector2 start = {x_springdelta * i, (HEIGHT * 0.6) -
                                            ((float)MASS_WIDTH / 2) +
                                            ((float)SPRING_ELEM_LENGTH / 2)};
    Vector2 end = {start.x + x_springdelta, start.y - y_end};
    springElements[i] = (SpringEl){start, end};
    DrawLineEx(start, end, THICK, LIGHTGRAY);
  }
  for (int i = 1; i < NUM_SPRING_ELEMENTS; i += 2) {
    Vector2 start = springElements[i - 1].end;
    Vector2 end = {start.x + x_springdelta, start.y + y_end};
    springElements[i] = (SpringEl){start, end};
    DrawLineEx(start, end, THICK, LIGHTGRAY);
  }
}

void floorDraw(int HEIGHT, int WIDTH) {
  Vector2 start = {0, HEIGHT * 0.6};
  Vector2 end = {WIDTH, HEIGHT * 0.6};
  DrawLineEx(start, end, THICK, GRAY);
}

void massDraw(int HEIGHT, int WIDTH, float x_mass) {
  Rectangle rect = {x_mass, (HEIGHT * 0.6) - MASS_WIDTH - (float)THICK / 2,
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

  float dt;
  SetTargetFPS(FPS);
  float x_mass = (float)WIDTH / 2;
  float X_REST = (float)WIDTH / 3;

  // Start drawing loop
  while (!WindowShouldClose()) {
    int WIDTH = GetScreenWidth();
    int HEIGHT = GetScreenHeight();

    BeginDrawing();

    ClearBackground(BLACK);
    floorDraw(HEIGHT, WIDTH);

    dt = GetFrameTime();
    float fric = v > 0 ? -FRICTION : FRICTION;
    a = (-K * (x_mass - X_REST)) + fric;
    v += a * dt;
    x_mass += v * dt;
    massDraw(HEIGHT, WIDTH, x_mass);
    springDraw(HEIGHT, WIDTH, x_mass);
    DrawFPS(10, 10);

    DrawText("Spring Mass system simulator goes here!", WIDTH / 10, 100, 30,
             GREEN);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
