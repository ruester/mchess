#include "chesspieces.h"

#define PAWN   (1 << 0)
#define KNIGHT (1 << 1)
#define BISHOP (1 << 2)
#define ROOK   (1 << 3)
#define QUEEN  (1 << 4)
#define KING   (1 << 5)
#define COLOR  (1 << 6)
#define FREE   (1 << 7)

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
    *p = FREE;
}
