#include <stdio.h>
#include <stdlib.h>

#include "chesspieces.h"
#include "chessboard.h"

static void initialize_chessboard(struct chessboard *c)
{
    int i, j;
    
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            set_free(c->board[i][j]);
}

struct chessboard *new_chessboard(void)
{
    struct chessboard *c;
    
    if ((c = calloc(1, sizeof(struct chessboard))) == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    
    initialize_chessboard(c);
    
    return c;
}
