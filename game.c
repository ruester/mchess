#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "chessboard.h"
#include "chesspieces.h"
#include "game.h"

#define WHITE 0
#define BLACK 1

struct coordinate {
    int x, y;
};

static void do_move(struct chessboard *c, struct coordinate from, struct coordinate to)
{

}

static void print_coordinate(struct coordinate c, FILE *f)
{
    fprintf(f, "%c%d", c.x + 'a', 8 - c.y);
}

static struct coordinate to_coordinate(char s[LINE_MAX])
{
    struct coordinate ret;
    
    ret.x = -1;
    ret.y = -1;
    
    /* get x value */
    if (s[0] >= 'A' && s[0] <= 'H')
        ret.x = s[0] - 'A';
    
    if (s[0] >= 'a' && s[0] <= 'h')
        ret.x = s[0] -'a';
    
    if (s[1] >= 'A' && s[1] <= 'H')
        ret.x = s[1] - 'A';
    
    if (s[1] >= 'a' && s[1] <= 'h')
        ret.x = s[1] -'a';
    
    /* get y value */
    if (s[0] >= '1' && s[0] <= '8')
        ret.y = 7 - s[0] + '1';
    
    if (s[1] >= '1' && s[1] <= '8')
        ret.y = 7 - s[1] + '1';
    
    return ret;
}

static struct coordinate *get_possible_moves_king(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves_queen(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves_rook(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves_bishop(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves_knight(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves_pawn(struct chessboard *c, struct coordinate p)
{
    return NULL;
}

static struct coordinate *get_possible_moves(struct chessboard *c, struct coordinate p)
{
    char chesspiece;
    
    chesspiece = c->board[p.y][p.x];
    
    if (is_king(chesspiece))
        return get_possible_moves_king(c, p);
    
    if (is_queen(chesspiece))
        return get_possible_moves_queen(c, p);
    
    if (is_rook(chesspiece))
        return get_possible_moves_rook(c, p);
    
    if (is_bishop(chesspiece))
        return get_possible_moves_bishop(c, p);
    
    if (is_knight(chesspiece))
        return get_possible_moves_knight(c, p);
    
    if (is_pawn(chesspiece))
        return get_possible_moves_pawn(c, p);
    
    return NULL;
}

static char is_valid_move(struct chessboard *c, struct coordinate from, struct coordinate to, char color)
{
    struct coordinate *moves;
    int i;
    
    /* check from and to */
    if (from.x < 0 || from.x > 7 || from.y < 0 || from.y > 7
        || to.x < 0 || to.x > 7 || to.y < 0 || to.y > 7) {
        fprintf(stderr, "invalid coordinates\n");
        return 0;
    }
    
    /* check if there is a chess piece */
    if (is_free(c->board[from.y][from.x])) {
        fprintf(stderr, "there is no chess piece on field ");
        print_coordinate(from, stderr);
        fprintf(stderr, "\n");
        return 0;
    }
    
    /* check color */
    if (color == WHITE && is_black(c->board[from.y][from.x])) {
        fprintf(stderr, "the chess piece on field ");
        print_coordinate(from, stderr);
        fprintf(stderr, " is not yours\n");
        return 0;
    }
    
    /* check 'to' field */
    if (!is_free(c->board[to.y][to.x])) {
        if ((color == WHITE && is_white(c->board[to.y][to.x]))
            || (color == BLACK && is_black(c->board[to.y][to.x]))) {
            fprintf(stderr, "you cannot capture your own chess piece on field ");
            print_coordinate(to, stderr);
            fprintf(stderr, "\n");
            return 0;
        }
    }
    
    moves = get_possible_moves(c, from);
    
    if (moves == NULL) {
        fprintf(stderr, "you cannot move the chess piece on field ");
        print_coordinate(from, stderr);
        fprintf(stderr, "\n");
        return 0;
    }

    printf("chess piece on field ");
    print_coordinate(from, stdout);
    printf(" can go to:\n");

    for(i = 0; moves[i].x != -1 && moves[i].y != -1; i++) {
        print_coordinate(moves[i], stdout);
        printf("\n");
        /*
        if (moves[i].x == to.x && moves[i].y == to.y) {
            free(moves);
            return 1;
        }
        */
    }
    
    free(moves);
    return 0;
}

static void print_help()
{
    printf("***************\n"
           "* mChess v0.1 *\n"
           "***************\n"
           "\n"
           "~ enter coordinates to move a chess piece (e.g. 'b1 c3')\n"
           "~ enter 'q' to exit the game\n"
           "\n");
    
}

void play_chess()
{
    struct chessboard *c;
    char input1[LINE_MAX] = {0},
         input2[LINE_MAX] = {0};
    struct coordinate from, to;

    print_help();

    c = new_chessboard();

    do {
        print_chessboard(c, stdout);

        do {
            do {
                printf("your move: ");
                scanf("%s", input1);
                if (input1[0] == 'q') {
                    free(c);
                    exit(EXIT_SUCCESS);
                }
                scanf("%s", input2);
                getchar();
                if (strlen(input1) != 2 || strlen(input2) != 2)
                    fprintf(stderr, "invalid entry\n");
            } while(strlen(input1) != 2 || strlen(input2) != 2);

            from = to_coordinate(input1);
            to   = to_coordinate(input2);
        } while(!is_valid_move(c, from, to, WHITE));
        
        do_move(c, from, to);
    } while (!is_checkmate(c));
}
