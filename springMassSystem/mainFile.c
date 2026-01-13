#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <math.h>
#include <stdio.h>

#define THICK 5
#define MASS_WIDTH 100
#define FPS 240
#define NUM_SPRING_ELEMENTS 16

float v = 80;
float a = 2;
float K = 10.0f;
float FRICTION = 10.0f;
float X_REST;
float SPRING_ELEM_LENGTH = 60;

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

Rectangle massDraw(int HEIGHT, int WIDTH, float x_mass) {
  Rectangle rect = {x_mass, (HEIGHT * 0.6) - MASS_WIDTH - (float)THICK / 2,
                    MASS_WIDTH, MASS_WIDTH};
  DrawRectangleRec(rect, RED);
  return rect;
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

    GuiLoadStyleDefault();
    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, 0x1E1E1EFF);
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, 0x444444FF);
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xE0E0E0FF);

    GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, 0x2A2A2AFF);
    GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, 0xE0E0E0FF);
    GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, 0x555555FF);

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x333333FF);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x444444FF);
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x555555FF);

    ClearBackground(BLACK);

    floorDraw(HEIGHT, WIDTH);
    springDraw(HEIGHT, WIDTH, x_mass);
    Rectangle rect = massDraw(HEIGHT, WIDTH, x_mass);

    dt = GetFrameTime();
    float fric = v > 0 ? -FRICTION : FRICTION;
    a = (-K * (x_mass - X_REST)) + fric;
    v += a * dt;
    x_mass += v * dt;

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
      Vector2 m = GetMousePosition();
      if (CheckCollisionPointRec(m, rect)) {
        x_mass = m.x;
        v = 0;
      }
    }

    float panelWidth = 360;
    float panelX = WIDTH - panelWidth - 20;
    float controlWidth = 220;

    Rectangle panel = {panelX, 20, panelWidth, 280};

    float controlX = panel.x + (panel.width - controlWidth) / 2.0f;

    GuiPanel(panel, "Spring Controls");

    GuiSliderBar((Rectangle){controlX, panel.y + 50, 220, 20}, "Stiffness",
                 NULL, &K, 1, 100);

    GuiSliderBar((Rectangle){controlX, panel.y + 90, 220, 20}, "Friction", NULL,
                 &FRICTION, 0, 50);

    GuiSliderBar((Rectangle){controlX, panel.y + 130, 220, 20}, "Rest Pos",
                 NULL, &X_REST, WIDTH * 0.1f, WIDTH * 0.9f);

    GuiSliderBar((Rectangle){controlX, panel.y + 170, 220, 20}, "Spring Size",
                 NULL, &SPRING_ELEM_LENGTH, 20, 120);

    if (GuiButton((Rectangle){controlX, panel.y + 210, 220, 30},
                  "Reset System")) {
      x_mass = X_REST;
      v = 0;
    }

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
