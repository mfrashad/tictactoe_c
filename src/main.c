#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"

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
} Game;

typedef struct {
    int x;
    int y;
} Position;


void draw_x(int x, int y, int w){
    gfx_line(x, y, x+w, y+w);
    gfx_line(x+w, y, x, y+w);
}

void draw_o(int x, int y, int w){
    int r = w/2;
    gfx_circle(x+r, y+r, w);
}

void draw_board(Game *game) {
    int x_offset = (WIN_WIDTH - (SIDE_LENGTH * game->size)) / 2;
    int y_offset = (WIN_HEIGHT - (SIDE_LENGTH * game->size)) / 2;

    char *x = "x";
    char *o = "Hello World";

    gfx_color(255,255,255);
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++){
            gfx_rectangle(x_offset + SIDE_LENGTH * j, y_offset + SIDE_LENGTH * i, SIDE_LENGTH, SIDE_LENGTH);
            if (game->board[i][j] == X) draw_x(x_offset + 10 + SIDE_LENGTH * j, y_offset + 10 + SIDE_LENGTH * i, SIDE_LENGTH - 20);
            if (game->board[i][j] == O) draw_o(x_offset + 10 + SIDE_LENGTH * j, y_offset + 10 + SIDE_LENGTH * i, SIDE_LENGTH - 20);
        }
    }
}


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
    if(is_player_winner(game, last_move, O)) return O;
    if(is_player_winner(game, last_move, X)) return X;

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

void draw_board_cli(Game *game){
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++)
            printf("%3d  |", game->board[i][j]);
        printf("\n-----|-----|-----\n");
    }
}



void check_mouse_input(Game *game){
    int mouse_x = gfx_xpos();
    int mouse_y = gfx_ypos();

    int x_offset = (WIN_WIDTH - (SIDE_LENGTH * game->size)) / 2;
    int y_offset = (WIN_HEIGHT - (SIDE_LENGTH * game->size)) / 2;

    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++){
            //printf("x: %d - %d, \t y: %d - %d\n", x_offset + SIDE_LENGTH * j, x_offset + SIDE_LENGTH * (j+1), y_offset + SIDE_LENGTH * i, y_offset + SIDE_LENGTH * (i+1));
            if ((mouse_x >= x_offset + SIDE_LENGTH * j && mouse_x <= x_offset + SIDE_LENGTH * (j+1) ) &&
                (mouse_y >= y_offset + SIDE_LENGTH * i && mouse_y <= y_offset + SIDE_LENGTH * (i+1) )){
                move(game, create_position(j,i), O);
                gfx_clear();
                draw_board(game);
            }
        }
    }
}



int main()
{

    char c;
    Game *game = create_game(3);
    /*
    printf("%d\n", move(game, create_position(0, 0), O));
    printf("%d\n", move(game, create_position(0, 1), X));
    printf("%d\n", move(game, create_position(1, 1), O));
    */

    //Open a new window for drawing.
    gfx_open(WIN_WIDTH,WIN_HEIGHT,"Example Graphics Program");

    gfx_clear_color(0,0,0);
    gfx_clear();
    draw_board(game);
    while(1) {
        // Wait for the user to press a character.
        c = gfx_wait();
        if(c==0x01) check_mouse_input(game);
        if(c=='q') break;
        //if(c==0x01) printf("Coordinates: %d %d",gfx_xpos(),gfx_ypos());
    }
    
    return 0;
}
