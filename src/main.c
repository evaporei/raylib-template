#include <raylib.h>

int main(void) {
#ifndef DEBUG
    SetTraceLogLevel(LOG_ERROR);
#endif

    rlInitWindow(800, 450, "game");

    while (!rlWindowShouldClose()) {
        rlBeginDrawing();
            rlClearBackground(BLACK);
            rlDrawText("game content here.", 190, 200, 20, RAYWHITE);
        rlEndDrawing();
    }

    rlCloseWindow();

    return 0;
}
