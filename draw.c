#include <raylib.h>
#include "colors.h"
#include "draw.h"

void DrawBoard(int ColorTheme)
{
    ColorPair theme = PALETTE[ColorTheme];
    float spaceText = 0.5;
    float squareCount = 8 + spaceText;
    int squareLength = Min2(GetRenderWidth(), GetRenderHeight()) / squareCount;
    int extra = (GetRenderWidth() - squareCount * squareLength) / 2;

    // Draw the chess board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Color col = ((i + j) & 1) ? theme.black : theme.white;
            DrawRectangle(extra + squareLength * spaceText / 2 + i * squareLength, j * squareLength + squareLength * spaceText / 2, squareLength, squareLength, col);
        }
    }
}

int Min2(int x, int y)
{
    return x < y ? x : y;
}
