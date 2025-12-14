#ifndef MOVE_H
#define MOVE_H
#include "main.h"

void MovePiece(int initialRow, int initialCol, int finalRow, int finalCol);
void SetEmptyCell(Cell *cell);
void ValidateAndDevalidateMoves(PieceType Piece, int CellX, int CellY, int ColorTheme, bool selected);
void MoveValidation(int CellX, int CellY, int ColorTheme, PieceType type, Team team, bool moved);
// Replaced all validation functions with one function 

#endif