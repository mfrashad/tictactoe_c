#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "gfx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define SIDE_LENGTH 100

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
