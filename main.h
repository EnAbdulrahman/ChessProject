#ifndef MAIN_H
#define MAIN_H

#include <raylib.h>

// piece identity
typedef enum
{
    PIECE_NONE = 0, // explicitly say it's zero because NONE signifies 0
    PIECE_KING,
    PIECE_QUEEN,
    PIECE_ROOK,
    PIECE_BISHOP,
    PIECE_KNIGHT,
    PIECE_PAWN
} PieceType;

/* team / color */
typedef enum
{
    TEAM_WHITE,
    TEAM_BLACK
} Team;

/* single Piece struct used for all pieces */
typedef struct Piece
{
    PieceType type;
    Team team;
    char hasMoved;  /* for castling and pawn first-move */
    char enPassant; /* set for pawn that just moved two squares */
    int spriteId;   /* optional: index into sprite atlas */
    Texture2D texture;
} Piece;

typedef struct Cell
{
    int row, col; /* board coordinates (0..7) */
    Vector2 pos;  /* pixel position for rendering */
    Piece piece;
} Cell;

#endif