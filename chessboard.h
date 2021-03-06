#ifndef MCHESS_CHESSBOARD_H
#define MCHESS_CHESSBOARD_H

struct chessboard {
    char board[8][8];
};

extern struct chessboard *new_chessboard(void);
extern struct chessboard *copy_chessboard(struct chessboard *c);
extern void print_chessboard(struct chessboard *c, FILE * f);

#endif
