#include <stdio.h>

#include "chessboard.h"
#include "game.h"

void play_chess()
{
    struct chessboard *c;
    
    c = new_chessboard();
    
    print_chessboard(c, stdout);
    
    /* ask the user until he entered an valid turn
     * or want to quit the game */
}
