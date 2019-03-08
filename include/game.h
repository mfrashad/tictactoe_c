#include <stdbool.h>
#ifndef GAME_H
#define GAME_H

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

#endif