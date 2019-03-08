#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"


typedef enum {
  BLUE = -1,
  NONE,
  RED
} Player;

typedef struct {
    int size;
    int **board;
    int *row_scores;
    int *col_scores;
    int left_right_diagonal_scores;
    int right_left_diagonal_scores;
} Game;

typedef struct {
    int x;
    int y;
} Position;

Game *create_game(int size) {
    Game *g = malloc(sizeof(Game));
    g->size = size;
    g->board = malloc(size * sizeof(int *));

    for(int i = 0; i < size; i++) g->board[i] = malloc(size * sizeof(int));

    g->row_scores = calloc(size, sizeof(int));
    g->col_scores = calloc(size, sizeof(int));
    g->left_right_diagonal_scores = 0;
    g->right_left_diagonal_scores = 0;

    return g;
}

bool is_player_winner(Game *game, Position *last_move, Player player) {
    int win_score = game->size * player;

    if (game->row_scores[last_move->y] == win_score ||
        game->col_scores[last_move->x] == win_score ||
        game->left_right_diagonal_scores == win_score ||
        game->right_left_diagonal_scores == win_score) {
        return true;
    } else {
        return false;
    }
}

Player check_winner(Game *game, Position *last_move) {
    if(is_player_winner(game, last_move, BLUE)) return BLUE;
    if(is_player_winner(game, last_move, RED)) return RED;

    return NONE;
}

Player move(Game *game, Position *last_move, Player player) {
    game->board[last_move->y][last_move->x] = player;
    game->row_scores[last_move->y] += player;
    game->col_scores[last_move->x] += player;
    
    if(last_move->x == last_move->y) {
        game->left_right_diagonal_scores += player;
    }

    if(last_move->x == game->size - last_move->y) {
        game->right_left_diagonal_scores += player;
    }

    return check_winner(game, last_move);
}

Position *create_position(int x, int y) {
    Position *position = malloc(sizeof(position));
    position->x = x;
    position->y = y;

    return position;
}

void draw_board(Game *game){
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++)
            printf("%3d  |", game->board[i][j]);
        printf("\n-----|-----|-----\n");
    }
}

int main()
{
    int ysize = 600;
    int xsize = 800;

    char c;
    Game *game = create_game(3);
    printf("%d\n", move(game, create_position(0, 0), BLUE));
    printf("%d\n", move(game, create_position(0, 1), RED));
    printf("%d\n", move(game, create_position(1, 1), BLUE));
    draw_board(game);


    /* Open a new window for drawing.
    gfx_open(xsize,ysize,"Example Graphics Program");

    gfx_clear_color(0,0,0);
    gfx_clear();
    while(1) {
        // Wait for the user to press a character.
        c = gfx_wait();
        if(c=='q') break;
    }
    */
    return 0;
}
