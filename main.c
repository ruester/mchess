#include <stdio.h>

#include "chessboard.h"

int main(int argc, char *argv[])
{
    struct chessboard *c;
    
    c = new_chessboard();
    
    printf("%d\n", c->board[5][5]);
    
    return 0;
}
