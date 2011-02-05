#include <stdio.h>

#include "chesspieces.h"

#define DEBUG

/* 
 * checking functions
 */
char is_king(char p)
{
    return (p & KING) == KING;
}

char is_queen(char p)
{
    return (p & QUEEN) == QUEEN;
}

char is_rook(char p)
{
    return (p & ROOK) == ROOK;
}

char is_bishop(char p)
{
    return (p & BISHOP) == BISHOP;
}

char is_knight(char p)
{
    return (p & KNIGHT) == KNIGHT;
}

char is_pawn(char p)
{
    return (p & PAWN) == PAWN;
}

char is_black(char p)
{
    return (p & COLOR) == COLOR;
}

char is_white(char p)
{
    if (is_free(p))
        return 0;
    
    return !is_black(p);
}

char is_free(char p)
{
    return (p & FREE) == FREE;
}

/*
 * setting functions
 */
void set_king(char *p)
{
    *p |= KING;
}

void set_queen(char *p)
{
    *p |= QUEEN;
}

void set_rook(char *p)
{
    *p |= ROOK;
}

void set_bishop(char *p)
{
    *p |= BISHOP;
}

void set_knight(char *p)
{
    *p |= KNIGHT;
}

void set_pawn(char *p)
{
    *p |= PAWN;
}

void set_black(char *p)
{
    *p |= COLOR;
}

void set_white(char *p)
{
    *p &= ~COLOR;
}

void set_free(char *p)
{
    *p = (char) FREE;
}

/*
 * unsetting functions
 */
void unset_pawn(char *p)
{
    *p &= ~PAWN;
}

void print_chesspiece(char p, FILE * f)
{
    char output, black;

    output = '?';

    if (is_black(p))
        black = 1;
    else
        black = 0;

    if (is_king(p))
        output = 'K';

    if (is_queen(p))
        output = 'Q';

    if (is_rook(p))
        output = 'R';

    if (is_bishop(p))
        output = 'B';

    if (is_knight(p))
        output = 'N';

    if (is_pawn(p))
        output = 'P';

    if (black)
        output += 'a' - 'A';

    if (is_free(p))
        output = ' ';

    fprintf(f, "%c", output);
}

char get_chesspiece(char p)
{
    if (is_king(p))
        return KING;
    
    if (is_queen(p))
        return QUEEN;
    
    if (is_rook(p))
        return ROOK;
    
    if (is_bishop(p))
        return BISHOP;
    
    if (is_knight(p))
        return KNIGHT;
    
    if (is_pawn(p))
        return PAWN;
    
#ifdef DEBUG
    fprintf(stderr, "get_chesspiece: wrong call\n");
#endif
    
    return ERROR;
}
