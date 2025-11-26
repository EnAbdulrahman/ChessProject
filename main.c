#include <raylib.h>
#include "colors.h"
#include "draw.h"

int main(void)
{
    // Initialize the game window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Chess");
    SetWindowMinSize(720, 720);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUND);
        DrawBoard(THEME_BROWN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
