#include <stdio.h>
#include <stdlib.h>

#include "chesspieces.h"
#include "chessboard.h"

static void initialize_chessboard(struct chessboard *c)
{
    int x, y;
    
    /* color */
    for (y = 0; y < 2; y++)
        for (x = 0; x < 8; x++)
            set_black(&(c->board[y][x]));
    
    /* kings */
    set_king(&(c->board[0][4]));
    set_king(&(c->board[7][4]));
    
    /* queens */
    set_queen(&(c->board[0][3]));
    set_queen(&(c->board[7][3]));
    
    /* rooks */
    set_rook(&(c->board[0][0]));
    set_rook(&(c->board[0][7]));
    set_rook(&(c->board[7][0]));
    set_rook(&(c->board[7][7]));
    
    /* bishops */
    set_bishop(&(c->board[0][2]));
    set_bishop(&(c->board[0][5]));
    set_bishop(&(c->board[7][2]));
    set_bishop(&(c->board[7][5]));

    /* knights */
    set_knight(&(c->board[0][1]));
    set_knight(&(c->board[0][6]));
    set_knight(&(c->board[7][1]));
    set_knight(&(c->board[7][6]));

    /* pawns */
    for (x = 0; x < 8; x++) {
        set_pawn(&(c->board[1][x]));
        set_pawn(&(c->board[6][x]));
    }
    
    /* free fields */
    for (y = 2; y < 6; y++)
        for (x = 0; x < 8; x++)
            set_free(&(c->board[y][x]));
}

struct chessboard *new_chessboard(void)
{
    struct chessboard *c;
    
    if ((c = calloc(1, sizeof(struct chessboard))) == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    
    initialize_chessboard(c);
    
    print_chessboard(c, stdout);
    
    return c;
}

void print_chessboard(struct chessboard *c, FILE *f)
{
    int x, y;
    
    for (y = 0; y < 8; y++) {
        for (x = 0; x < 8; x++) {
            print_chesspiece(c->board[y][x], f);
            if (x != 7)
                printf(" ");
        }
        
        printf("\n");
    }
    
}
