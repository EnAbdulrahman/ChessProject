#include <raylib.h>
#include <stdio.h>
#include "colors.h"
#include "draw.h"
#include "main.h"

Cell GameBoard[8][8];

int main(void)
{
    // Initialize the game window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 720, "Chess");
    SetWindowMinSize(720, 720);

    SetTargetFPS(60);

    LoadPiece(0, 0, PIECE_KING, TEAM_WHITE, ComputeSquareLength());
    // LoadPiece(0, 0, PIECE_KING, TEAM_WHITE, 100);

#ifdef DEBUG
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", GameBoard[i][j].piece.type);
        }
        printf("\n");
    }
#endif

    while (!WindowShouldClose())
    {
        if (IsWindowResized())
            LoadPiece(0, 0, PIECE_KING, TEAM_WHITE, ComputeSquareLength());

        BeginDrawing();
        ClearBackground(BACKGROUND);
        DrawBoard(THEME_BROWN);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
