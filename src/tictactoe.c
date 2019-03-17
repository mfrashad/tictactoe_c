#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "tictactoe.h"

extern int stat[2][TOTAL_SIZE][TOTAL_DATA];
extern GameState game_state;
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

void reset_stat(){
    for(int i=0;i<2;i++){
        for(int j=0;j<TOTAL_SIZE; j++){
            for(int k=0; k<TOTAL_DATA; k++){
                stat[i][j][k] = 0;
            }
        }
    }
}

bool read_stat(){
    FILE *f;
    if((f = fopen("stat.data", "rb")) == NULL) {
        printf("Error opening file");
        return false;
    }
    fread(stat, sizeof(int) * 2*TOTAL_SIZE*TOTAL_DATA, 1, f);
    fclose(f);
    return true;
}

bool save_stat(){
    int written = 0;
    FILE *f = fopen("stat.data", "wb");
    written = fwrite(stat, sizeof(int)*2*TOTAL_SIZE*TOTAL_DATA, 1, f);
    if(written == 0) {
        printf("Error writing file");
        return false;
    }
    fclose(f);
    return true;
}

void check_game_input(Game *game, char c, int mouse_x, int mouse_y){

    int x_offset = (WIN_WIDTH - (SIDE_LENGTH * game->size)) / 2;
    int y_offset = (WIN_HEIGHT - (SIDE_LENGTH * game->size)) / 2;

    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++){
            //printf("x: %d - %d, \t y: %d - %d\n", x_offset + SIDE_LENGTH * j, x_offset + SIDE_LENGTH * (j+1), y_offset + SIDE_LENGTH * i, y_offset + SIDE_LENGTH * (i+1));

            bool is_mouse = (c == 0x01);
            bool is_button_pressed = is_mouse && 
                                     (mouse_x >= x_offset + SIDE_LENGTH * j && mouse_x <= x_offset + SIDE_LENGTH * (j+1) ) && 
                                     (mouse_y >= y_offset + SIDE_LENGTH * i && mouse_y <= y_offset + SIDE_LENGTH * (i+1) );

            bool is_number_pressed = c == (48 + j+1 + i*game->size);

            if (is_button_pressed || is_number_pressed){
                move(game, create_position(j,i), game->next_turn);
                if(game->winner || game->draw) game_state = GAME_WIN;
            }
        }
    }
}