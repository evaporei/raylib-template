#include "raylib.h"

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif

    InitWindow(800, 450, "mario");

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("mario will jump here.", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
