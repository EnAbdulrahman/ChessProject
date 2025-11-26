#include <raylib.h>
#include <string.h>
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include "colors.h"
#include "draw.h"
#include "main.h"

// access the GameBoard from the main.c file
extern Cell GameBoard[8][8];

// Local Prototypes
static int Min2(int x, int y);
static void LoadHelper(char *pieceNameBuffer, int bufferSize, const char *pieceName, Team team, int squareLength, int row, int col, PieceType type);
static void InitializeCellsPos(int extra, int squareLength, float spaceText);
static size_t TrimTrailingWhitespace(char *s);
static void displayPieces(void);

#define SPACETEXT 0.5f

void DrawBoard(int ColorTheme)
{
    ColorPair theme = PALETTE[ColorTheme];
    float squareCount = 8 + SPACETEXT;
    int squareLength = ComputeSquareLength(&squareCount);
    int extra = (GetRenderWidth() - squareCount * squareLength) / 2;

    // if (IsWindowResized())
    InitializeCellsPos(extra, squareLength, SPACETEXT);

    // Draw the chess board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Color col = ((i + j) & 1) ? theme.black : theme.white;
            DrawRectangleV(GameBoard[i][j].pos, (Vector2){squareLength, squareLength}, col);
        }
    }

    displayPieces();
}

void LoadPiece(int row, int col, PieceType type, Team team, int squareLength)
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return;

    char pieceName[64];

    switch (type)
    {
    case PIECE_PAWN:
        LoadHelper(pieceName, sizeof pieceName, "pawn", team, squareLength, row, col, type);
        break;
    case PIECE_KNIGHT:
        LoadHelper(pieceName, sizeof pieceName, "knight", team, squareLength, row, col, type);
        break;
    case PIECE_BISHOP:
        LoadHelper(pieceName, sizeof pieceName, "bishop", team, squareLength, row, col, type);
        break;
    case PIECE_ROOK:
        LoadHelper(pieceName, sizeof pieceName, "rook", team, squareLength, row, col, type);
        break;
    case PIECE_QUEEN:
        LoadHelper(pieceName, sizeof pieceName, "queen", team, squareLength, row, col, type);
        break;
    case PIECE_KING:
        LoadHelper(pieceName, sizeof pieceName, "king", team, squareLength, row, col, type);
        break;
    default:
        break;
    }
}

static void LoadHelper(char *pieceNameBuffer, int bufferSize, const char *pieceName, Team team, int squareLength, int row, int col, PieceType type)
{
    int n = snprintf(pieceNameBuffer, (size_t)bufferSize, "assets/%s%c.png", pieceName, (team == TEAM_WHITE) ? 'W' : 'B');
    if (n < 0)
        return;
    if (n >= bufferSize)
        TraceLog(LOG_WARNING, "Filename was truncated: %s", pieceNameBuffer);

    TrimTrailingWhitespace(pieceNameBuffer);

    Image image = LoadImage(pieceNameBuffer);
    if (!image.data || image.width == 0 || image.height == 0)
    {
        TraceLog(LOG_WARNING, "Failed to load image: %s", pieceNameBuffer);
        return;
    }

    ImageResize(&image, squareLength, squareLength);
    Texture2D tex = LoadTextureFromImage(image);
    UnloadImage(image);

    // id = 0 means no valid texture
    if (tex.id == 0)
    {
        TraceLog(LOG_WARNING, "Failed to create texture from image: %s", pieceNameBuffer);
        return;
    }

    // unload previous texture if present
    if (GameBoard[row][col].piece.texture.id != 0)
        UnloadTexture(GameBoard[row][col].piece.texture);

    GameBoard[row][col].piece.texture = tex;
    GameBoard[row][col].piece.type = type;
}

static void displayPieces(void)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (GameBoard[i][j].piece.type != PIECE_NONE)
            {
                DrawTextureV(GameBoard[i][j].piece.texture, GameBoard[i][j].pos, WHITE);
            }
        }
    }
}

static void InitializeCellsPos(int extra, int squareLength, float spaceText)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            GameBoard[i][j].pos = (Vector2){extra + squareLength * spaceText / 2 + i * squareLength, j * squareLength + squareLength * spaceText / 2};
        }
    }
}

static size_t TrimTrailingWhitespace(char *s)
{
    // Check to see if it's an empty sting
    if (!s)
        return 0;
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1]))
        len--;
    s[len] = '\0';
    return len;
}

static int Min2(int x, int y)
{
    return x < y ? x : y;
}

int ComputeSquareLength()
{
    float squareCount = 8 + SPACETEXT;
    return Min2(GetRenderWidth(), GetRenderHeight()) / squareCount;
}
