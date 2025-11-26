#include <raylib.h>

int main(void)
{
    InitWindow(1280, 720, "Chess");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}