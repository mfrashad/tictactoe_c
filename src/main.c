#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"
#include "tictactoe.h"
#include "draw.h"
#include "menu.h"
#include "game.h"

GameState game_state = MAIN_MENU;
Game *game;

void draw_board_cli(Game *game){
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++)
            printf("%3d  |", game->board[i][j]);
        printf("\n-----|-----|-----\n");
    }
}



void check_game_input(char c, Game *game){
    int mouse_x = gfx_xpos();
    int mouse_y = gfx_ypos();

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



int main()
{

    char c;
    game = create_game(3);

    //Open a new window for drawing.
    gfx_open(WIN_WIDTH,WIN_HEIGHT,"Tic Tac Toe Project");

    gfx_clear_color(0,0,0);
    gfx_clear();

    
    Menu *mode_menu = create_mode_menu();
    Menu *start_menu = create_start_menu();
    Menu *size_menu = create_size_menu();
    Menu *player_menu = create_player_menu();
    Menu *statistic_menu = create_statistic_menu();
    
    //draw_board(game);
    bool loop = true;
    while(loop) {
        // Wait for the user to press a character.
        switch(game_state) {
            case STATISTIC:
                gfx_clear();
                draw_menu(statistic_menu);
                draw_statistic();
                c = gfx_wait();
                check_menu_input(c, statistic_menu);
                break;
            case MAIN_MENU:
                gfx_clear();
                draw_menu(start_menu);
                c = gfx_wait();
                check_menu_input(c, start_menu);
                break;
            case SIZE_MENU:
                gfx_clear();
                draw_menu(size_menu);
                c = gfx_wait();
                check_menu_input(c, size_menu);
                break;
            case MODE_MENU:
                gfx_clear();
                draw_menu(mode_menu);
                c = gfx_wait();
                check_menu_input(c, mode_menu);
                break;
            case PLAYER_MENU:
                gfx_clear();
                draw_menu(player_menu);
                c = gfx_wait();
                check_menu_input(c, player_menu);
                break;
            case GAME1:
                gfx_clear();
                if(game->next_turn != game->player) computer_move(game);
                if(game->winner || game->draw) {
                    game_state = GAME_WIN;
                } else {
                    draw_board(game);
                    c = gfx_wait();
                    check_game_input(c, game);
                }
                break;
            case GAME2:
                gfx_clear();
                draw_board(game);
                c = gfx_wait();
                check_game_input(c, game);
                break;
            case GAME_WIN:
                gfx_clear();
                draw_board(game);
                draw_win_text(game->winner);
                Menu *win_menu = create_win_menu(game);
                draw_menu(win_menu);
                c = gfx_wait();
                check_menu_input(c, win_menu);
                free(win_menu);
                break;
            case QUIT:
                loop = false;
                break;

                
        }
        if(c=='q') break;
        //if(c==0x01) printf("Coordinates: %d %d",gfx_xpos(),gfx_ypos());
        
    }
    
    return 0;
}
