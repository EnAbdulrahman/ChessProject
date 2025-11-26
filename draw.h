#ifndef DRAW_H
#define DRAW_H

#include "main.h"

void DrawBoard(int ColorTheme);
void LoadPiece(int row, int col, PieceType type, Team team, int squareLength);
int ComputeSquareLength();

#endif