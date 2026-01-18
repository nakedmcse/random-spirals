// Random Spirals
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "raylib.h"
#include "types.h"

// Global constants
const int screenWidth = 800;
const int screenHeight = 800;
const int targetFPS = 200;


void InitGame() {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Random Numbers on a Circular Plane");
    SetTargetFPS(targetFPS);
}

Vector2 ProjectPoint(int radius, int angle) {
    Vector2 newPoint;
    float a = (float)angle * (PI / 180.0f);
    newPoint.x = (float)radius * cosf(a);
    newPoint.y = (float)radius * sinf(a);
    return newPoint;
}

Color ColorPoint(int radius) {
    Color spectrum[] = { RAYWHITE, SKYBLUE, GREEN, YELLOW, RED };
    return spectrum[radius % (sizeof(spectrum) / sizeof(Color))];
}

static inline float Remap(float v, float inMin, float inMax, float outMin, float outMax) {
    if (inMax - inMin == 0) return (outMin + outMax) * 0.5f;
    float t = (v - inMin) / (inMax - inMin);
    return outMin + t * (outMax - outMin);
}

Vector2 TransformPoint(Vector2 p, float minX, float maxX, float minY, float maxY) {
    Vector2 out;
    out.x = Remap(p.x, minX, maxX, 20.0f, (float)screenWidth  - 21.0f);
    out.y = Remap(p.y, minY, maxY, 20.0f, (float)screenHeight - 21.0f);
    return out;
}

void RenderPoints(pointsArray *p, float minX, float maxX, float minY, float maxY) {
    for (int i = 0; i < p->size; i++) {
        const Vector2 transformed = TransformPoint(p->points[i].point, minX, maxX, minY, maxY);
        DrawCircle((int)transformed.x, (int)transformed.y, 2.0f, p->points[i].color);
    }
}

int main(void) {
    bool pause = false;
    int frameCount = 0;
    int nextInt = 0;
    float minX = 0, maxX = 0, minY = 0, maxY = 0;
    bool haveBounds = false;
    char sizeBuffer[100];
    pointsArray points = {NULL, 0};

    srand((unsigned)time(NULL));

    InitGame();

    while (!WindowShouldClose()) {
        // Update Points
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        if (IsKeyPressed(KEY_Q)) break;

        if (!pause) {
            int prevInt = nextInt;
            nextInt += (rand() % 20) + 1;
            const Vector2 newPoint = ProjectPoint(prevInt, nextInt);
            if (!haveBounds) {
                minX = maxX = newPoint.x;
                minY = maxY = newPoint.y;
                haveBounds = true;
            } else {
                if (newPoint.x < minX) minX = newPoint.x;
                if (newPoint.x > maxX) maxX = newPoint.x;
                if (newPoint.y < minY) minY = newPoint.y;
                if (newPoint.y > maxY) maxY = newPoint.y;
            }
            const Color newColor = ColorPoint(prevInt);
            const spiralPoint sp = { newPoint, newColor };
            appendPoint(&points, sp);
        }
        else frameCount++;

        // Render Points
        BeginDrawing();
        ClearBackground(DARKGRAY);
        RenderPoints(&points, minX, maxX, minY, maxY);
        DrawText("PRESS SPACE to PAUSE, Q to QUIT", 10, GetScreenHeight() - 25, 20, LIGHTGRAY);
        sprintf(sizeBuffer, "%lu", points.size);
        DrawText(sizeBuffer, screenWidth-100, GetScreenHeight() - 25, 20, LIGHTGRAY);
        DrawFPS(10,10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}