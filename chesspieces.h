#ifndef MCHESS_CHESSPIECES_H
#define MCHESS_CHESSPIECES_H

/* checking functions */
extern char is_king(char p);
extern char is_queen(char p);
extern char is_rook(char p);
extern char is_bishop(char p);
extern char is_knight(char p);
extern char is_pawn(char p);
extern char is_black(char p);
extern char is_white(char p);
extern char is_free(char p);

/* setting functions */
extern void set_king(char *p);
extern void set_queen(char *p);
extern void set_rook(char *p);
extern void set_bishop(char *p);
extern void set_knight(char *p);
extern void set_pawn(char *p);
extern void set_black(char *p);
extern void set_white(char *p);
extern void set_free(char *p);

#endif
