#include <stdlib.h>
#include "tictactoe.h"
#include "gfx.h"

extern int stat[2][2][10];
Game *create_game(int size) {
    Game *g = malloc(sizeof(Game));
    g->size = size;
    g->board = malloc(size * sizeof(int *));

    for(int i = 0; i < size; i++){
        g->board[i] = calloc(size, sizeof(int));
    }
    g->row_scores = calloc(size, sizeof(int));
    g->col_scores = calloc(size, sizeof(int));
    g->left_right_diagonal_scores = 0;
    g->right_left_diagonal_scores = 0;
    g->next_turn = O;
    g->winner = 0;
    g->mode = MULTI;
    g->draw = false;

    return g;
}

void reset(Game **game){
    Game *new_game = create_game((*game)->size);
    *game = new_game;
}

void resize(Game **game, int size){
    Game *new_game = create_game(size);
    *game = new_game;
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
    if(is_player_winner(game, last_move, O)) return O;
    if(is_player_winner(game, last_move, X)) return X;

    return NONE;
}

Player move(Game *game, Position *last_move, Player player) {
    if(!game->board[last_move->y][last_move->x]){
        game->board[last_move->y][last_move->x] = player;
        game->row_scores[last_move->y] += player;
        game->col_scores[last_move->x] += player;

        if(last_move->x == last_move->y) {
            game->left_right_diagonal_scores += player;
        }

        if(last_move->x == game->size - 1 - last_move->y) {
            game->right_left_diagonal_scores += player;
        }

        game->next_turn = player == O ? X : O;
    }
    
    game->winner = check_winner(game, last_move);
    game->draw = is_draw(game);
    record_stat(game);
    return game->winner;
}

void record_stat(Game *game){
    if(game->winner || game->draw){
        int size = game->size == 3 ? SIZE_3 : SIZE_5;
        stat[game->mode][size][GAMES_PLAYED]++;
        if(game->draw) {
            stat[game->mode][size][GAMES_DRAW]++;
            return;
        }
        switch(game->mode){
            case SINGLE:
                if(game->winner != game->player) {
                    stat[game->mode][size][COMPUTER_WON]++;
                } else {
                    stat[game->mode][size][COMPUTER_LOST]++;
                }
                stat[game->mode][size][USER_WON] = stat[game->mode][size][COMPUTER_LOST];
                stat[game->mode][size][USER_LOST] = stat[game->mode][size][COMPUTER_WON];
                break;
            case MULTI:
                if(game->winner == X) {
                    stat[game->mode][size][X_WON]++;
                } else {
                    stat[game->mode][size][X_LOST]++;    
                }
                stat[game->mode][size][O_WON] = stat[game->mode][size][X_LOST];
                stat[game->mode][size][O_LOST] = stat[game->mode][size][X_WON];
                break;
        }
    }
}

bool is_draw(Game *game){
    for(int i=0; i<game->size; i++){
        for(int j=0; j<game->size; j++){
            if(game->board[i][j] == NONE){
                return false;
            }
        }
    }
    return true;
}

void computer_move(Game *game){
    if(is_draw(game)) return;
    Player computer = game->player == O ? X : O;
    int i,j;
    do {
        i = rand() % game->size;
        j = rand() % game->size;
    } while(game->board[i][j] != NONE);
    move(game, create_position(j,i), computer);
}

Position *create_position(int x, int y) {
    Position *position = malloc(sizeof(position));
    position->x = x;
    position->y = y;

    return position;
}

void win(Player winner) {
    char *str;
    if(winner==O) str = "Player O wins";
    if(winner==X) str = "Player X wins";
    gfx_text(str, 200, 100);
}