#include <stdbool.h>
#ifndef GAME_H
#define GAME_H

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SIDE_LENGTH 100

typedef enum {
  O = -1,
  NONE,
  X
} Player;

typedef struct {
    int size;
    int **board;
    int *row_scores;
    int *col_scores;
    int left_right_diagonal_scores;
    int right_left_diagonal_scores;
    int next_turn;
} Game;

typedef struct {
    int x;
    int y;
} Position;


Game *create_game(int size);

bool is_player_winner(Game *game, Position *last_move, Player player);

Player check_winner(Game *game, Position *last_move);

Player move(Game *game, Position *last_move, Player player);

Position *create_position(int x, int y);

void win(Player winner);

#endif