#ifndef MCHESS_CHESSPIECES_H
#define MCHESS_CHESSPIECES_H

#define PAWN   (1 << 0)
#define KNIGHT (1 << 1)
#define BISHOP (1 << 2)
#define ROOK   (1 << 3)
#define QUEEN  (1 << 4)
#define KING   (1 << 5)
#define COLOR  (1 << 6)
#define FREE   (1 << 7)

#define ERROR  (-1)

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

/* unsetting functions */
extern void unset_pawn(char *p);

extern void print_chesspiece(char p, FILE * f);
extern char get_chesspiece(char p);

#endif
