#include <stdbool.h>
#ifndef GAME_H
#define GAME_H

#define WIN_WIDTH 1200
#define WIN_HEIGHT 700
#define SIDE_LENGTH 100

typedef enum {
  O = -1,
  NONE,
  X
} Player;

typedef enum {
    SINGLE,
    MULTI
} GameMode;

typedef enum {
    SIZE_3,
    SIZE_5,
    TOTAL_SIZE
} BOARD_SIZE;

typedef struct {
    int size;
    int **board;
    int *row_scores;
    int *col_scores;
    int left_right_diagonal_scores;
    int right_left_diagonal_scores;
    int next_turn;
    bool draw;
    GameMode mode;
    Player player;
    Player winner;
} Game;

typedef struct {
    int x;
    int y;
} Position;

typedef enum {
    GAMES_PLAYED = 0,
    GAMES_DRAW,
    COMPUTER_WON,
    COMPUTER_LOST,
    USER_WON,
    USER_LOST,
    X_WON,
    X_LOST,
    O_WON,
    O_LOST,
    TOTAL_DATA    
} Data;

typedef struct {
    int data[2][2][10];
} Stat;


Game *create_game(int size);

void reset(Game **game);

void resize(Game **game, int size);

bool is_player_winner(Game *game, Position *last_move, Player player);

bool is_draw(Game *game);

Player check_winner(Game *game, Position *last_move);

Player move(Game *game, Position *last_move, Player player);

void computer_move(Game *game);

Position *create_position(int x, int y);

void win(Player winner);

void check_game_input(Game *game, char c, int mouse_x, int mouse_y);

Stat *create_stat();

void reset_stat();

bool read_stat();

bool save_stat();

void record_stat(Game *game);

#endif