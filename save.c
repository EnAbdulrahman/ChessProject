#include "main.h"
#include <stdlib.h>
#include <raylib.h>
#include <ctype.h>
#include "save.h"

// TODO We must a add a small letter of the whole string to decide who is going to play next w or b

extern Cell GameBoard[8][8];

char *SaveFEN(void)
{
    // Big initial buffer size
    char *out = malloc(128 * sizeof(char));
    if (out == NULL)
    {
        TraceLog(LOG_WARNING, "Couldn't allocate space for the FEN string");
        return NULL;
    }

    int consecutiveEmptyCells = 0;
    char currentPiece;
    int counter = 0;

    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            PieceType type = GameBoard[row][col].piece.type;
            Team team = GameBoard[row][col].piece.team;

            if (type != PIECE_NONE)
            {
                if (consecutiveEmptyCells != 0)
                {
                    out[counter++] = '0' + consecutiveEmptyCells;
                    consecutiveEmptyCells = 0; /* reset after flushing */
                }

                switch (type)
                {
                case PIECE_BISHOP:
                    currentPiece = 'b';
                    break;
                case PIECE_KING:
                    currentPiece = 'k';
                    break;
                case PIECE_KNIGHT:
                    currentPiece = 'n';
                    break;
                case PIECE_PAWN:
                    currentPiece = 'p';
                    break;
                case PIECE_QUEEN:
                    currentPiece = 'q';
                    break;
                case PIECE_ROOK:
                    currentPiece = 'r';
                    break;
                default:
                    TraceLog(LOG_WARNING, "invalid character %c for piece type", type);
                    free(out);
                    return NULL;
                }

                currentPiece = (team == TEAM_BLACK ? currentPiece : toupper(currentPiece));

                out[counter++] = currentPiece;
            }
            else
            {
                consecutiveEmptyCells++;
            }
        }

        /* flush any remaining empty count at end of rank */
        if (consecutiveEmptyCells != 0)
        {
            out[counter++] = '0' + consecutiveEmptyCells;
            consecutiveEmptyCells = 0;
        }

        /* add rank separator except after the last rank */
        if (row < 7)
        {
            out[counter++] = '/';
        }
    }

    /* ensure space for NUL terminator */
    char *temp = realloc(out, counter + 1);
    if (temp == NULL)
    {
        free(out);
        TraceLog(LOG_WARNING, "Failed to resize the buffer");
        return NULL;
    }

    out = temp;
    out[counter] = '\0';

    return out;
}
