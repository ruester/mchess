#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "chessboard.h"
#include "chesspieces.h"
#include "game.h"

#define WHITE 0
#define BLACK 1

#define DEBUG

/* structures */
struct coordinate {
    int x, y;
};

/* global variables */
char enpassant_possible = 0;
struct coordinate enpassant;
char current_player = WHITE;

/* prototypes */
static void do_move(struct chessboard *c, struct coordinate from, struct coordinate to);
static void print_coordinate(struct coordinate c, FILE *f);
static struct coordinate to_coordinate(char s[LINE_MAX]);
static char check_pin(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_king(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_queen(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_rook(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_bishop(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_knight(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves_pawn(struct chessboard *c, struct coordinate p);
static struct coordinate *get_possible_moves(struct chessboard *c, struct coordinate p);
static char is_valid_move(struct chessboard *c, struct coordinate from, struct coordinate to, char color);
static void do_move_ai();
static char is_check(struct chessboard *c);
static char is_checkmate(struct chessboard *c);
static void print_help();

/* move a chess piece */
static void do_move(struct chessboard *c, struct coordinate from, struct coordinate to)
{
    char type;
    
    type = get_chesspiece(c->board[from.y][from.x]);
    
    if (enpassant_possible) {
        if (is_pawn(c->board[from.y][from.x]) && to.x == enpassant.x && to.y == enpassant.y) {
            if (is_white(c->board[from.y][from.x]))
                set_free(&(c->board[to.y + 1][to.x]));
            else
                set_free(&(c->board[to.y - 1][to.x]));
        }
        enpassant_possible = 0;
        enpassant.x = -1;
        enpassant.y = -1;
    }
    
    if (is_pawn(c->board[from.y][from.x])
        && (to.y - 2 == from.y || to.y + 2 == from.y)) {
        enpassant_possible = 1;
        enpassant.x = from.x;
        enpassant.y = (from.y + to.y) / 2;
    }
    
    if (current_player == WHITE)
        current_player = BLACK;
    else
        current_player = WHITE;
    
    c->board[to.y][to.x] = c->board[from.y][from.x];
    set_free(&(c->board[from.y][from.x]));
    
    if (type == PAWN
        && (to.y == 0 || to.y == 7)) {
        /* TODO: ask for promotion */
        unset_pawn(&(c->board[to.y][to.x]));
        set_queen(&(c->board[to.y][to.x]));
    }
}

static void print_coordinate(struct coordinate c, FILE *f)
{
    fprintf(f, "%c%d", c.x + 'a', 8 - c.y);
}

/* convert coordinates given by character + number (e. g. 'a1')
 * to array coordinates */
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

/* check if the chess piece on the coordinate is pinned */
static char check_pin(struct chessboard *c, struct coordinate p)
{
    char temp, ret;
    
    /* memorize chess piece */
    temp = c->board[p.y][p.x];
    
    /* take away the chess piece */
    set_free(&(c->board[p.y][p.x]));
    
    /* check if there is a check situation */
    ret = is_check(c);
    
    /* place memorized chess piece again */
    c->board[p.y][p.x] = temp;
    
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
    struct coordinate *moves;
    int count;
    
    moves = NULL;
    count = 0;
    
    if (check_pin(c, p))
        return NULL;
    
    if (is_white(c->board[p.y][p.x])) {
        if (is_free(c->board[p.y - 1][p.x])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x;
            moves[count - 1].y = p.y - 1;
            
            if (p.y == 6 && is_free(c->board[4][p.x])) {
                count++;
                
                if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }

                moves[count - 1].x = p.x;
                moves[count - 1].y = 4;
            }
        }
        
        if (enpassant_possible) {
            if ((enpassant.x == p.x - 1 && enpassant.y == p.y - 1)
                || (enpassant.x == p.x + 1 && enpassant.y == p.y - 1)) {
                count++;
                
                if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }

                moves[count - 1].x = enpassant.x;
                moves[count - 1].y = enpassant.y;
            }
        }
        
        if (p.x > 0 && is_black(c->board[p.y - 1][p.x - 1])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x - 1;
            moves[count - 1].y = p.y - 1;
        }
        
        if (p.x < 7 && is_black(c->board[p.y - 1][p.x + 1])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x + 1;
            moves[count - 1].y = p.y - 1;
        }
    } else {
        if (is_free(c->board[p.y + 1][p.x])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x;
            moves[count - 1].y = p.y + 1;
            
            if (p.y == 1 && is_free(c->board[3][p.x])) {
                count++;
                
                if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }

                moves[count - 1].x = p.x;
                moves[count - 1].y = 3;
            }
        }
        
        if (enpassant_possible) {
            if ((enpassant.x == p.x - 1 && enpassant.y == p.y + 1)
                || (enpassant.x == p.x + 1 && enpassant.y == p.y + 1)) {
                count++;
                
                if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }

                moves[count - 1].x = enpassant.x;
                moves[count - 1].y = enpassant.y;
            }
        }
        
        if (p.x > 0 && is_white(c->board[p.y + 1][p.x - 1])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x - 1;
            moves[count - 1].y = p.y + 1;
        }
        
        if (p.x < 7 && is_white(c->board[p.y + 1][p.x + 1])) {
            count++;
            
            if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
            
            moves[count - 1].x = p.x + 1;
            moves[count - 1].y = p.y + 1;
        }
    }
    
    count++;
    
    if ((moves = realloc(moves, sizeof(struct coordinate) * count)) == NULL) {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    
    moves[count - 1].x = -1;
    moves[count - 1].y = -1;
    
    return moves;
}

/* returns the possible moves of the chess piece on the coordinate */
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

#ifdef DEBUG
    printf("chess piece on field ");
    print_coordinate(from, stdout);
    printf(" can go to:\n");

    for(i = 0; moves[i].x != -1 && moves[i].y != -1; i++) {
        print_coordinate(moves[i], stdout);
        printf("\n");
    }
#endif

    for(i = 0; moves[i].x != -1 && moves[i].y != -1; i++) {
        if (moves[i].x == to.x && moves[i].y == to.y) {
            free(moves);
            return 1;
        }
    }
    
    free(moves);
    
    fprintf(stderr, "you cannot move the chess piece on field ");
    print_coordinate(from, stderr);
    fprintf(stderr, " to ");
    print_coordinate(to, stderr);
    fprintf(stderr, "\n");
    return 0;
}

static void do_move_ai()
{
    /*
    struct coordinate from, to;
    
    get_good_move(c, &from, &to);
    be careful: is_valid_move(c, from, to, !!! BLACK !!!);
    
    do_move(c, from, to);
    */
}

static char is_check(struct chessboard *c)
{
    return 0;
}

static char is_checkmate(struct chessboard *c)
{
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

    srand(time(NULL));
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
        } while(!is_valid_move(c, from, to, current_player));
        
        do_move(c, from, to);
        do_move_ai(c);
    } while (!is_checkmate(c));
}
