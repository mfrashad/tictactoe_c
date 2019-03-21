#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gfx.h"
#include "tictactoe.h"
#include "draw.h"
#include "menu.h"

GameState game_state = MAIN_MENU;
Game *game;
bool keyboard_help = false;
int stat[2][TOTAL_SIZE][TOTAL_DATA] = {0};


void draw_board_cli(Game *game){
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++)
            printf("%3d  |", game->board[i][j]);
        printf("\n-----|-----|-----\n");
    }
}

void display_menu(char *c, Menu *menu){
    draw_menu(menu);
    *c = gfx_wait();
    check_menu_input(*c, menu);
}



int main()
{
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
    Menu *win_menu = create_win_menu(game);
    Menu *game_menu = create_game_menu(game);
    char c;
    read_stat();
    
    //draw_board(game);
    bool loop = true;
    while(loop) {
        gfx_clear();
        // Wait for the user to press a character.
        switch(game_state) {
            case STATISTIC:
                draw_statistic();
                display_menu(&c, statistic_menu);
                break;
            case MAIN_MENU:
                draw_keyboard_help_text();
                display_menu(&c, start_menu);
                break;
            case SIZE_MENU:
                display_menu(&c, size_menu);
                break;
            case MODE_MENU:
                display_menu(&c, mode_menu);
                break;
            case PLAYER_MENU:
                display_menu(&c, player_menu);
                break;
            case GAME1:
                if(game->next_turn != game->player) computer_move(game);
                if(game->winner || game->draw) {
                    game_state = GAME_WIN;
                } else {
                    change_button_onclick(game_menu->buttons[0], game->mode == SINGLE ? play1 : play2);
                    draw_menu(game_menu);
                    draw_board(game);
                    draw_game_text(game);
                    c = gfx_wait();
                    check_game_input(game, c, gfx_xpos(), gfx_ypos());
                    check_menu_input(c, game_menu);
                }
                break;
            case GAME2:
                draw_board(game);
                draw_game_text(game);
                c = gfx_wait();
                check_game_input(game, c, gfx_xpos(), gfx_ypos());
                break;
            case GAME_WIN:
                draw_board(game);
                draw_win_text(game->winner);
                change_button_onclick(win_menu->buttons[0], game->mode == SINGLE ? play1 : play2);
                display_menu(&c, win_menu);
                break;
            case QUIT:
                loop = false;
                save_stat();
                break;

                
        }
        if(c==0x09) keyboard_help = !keyboard_help; //TAB button
        if(c==0x1B) break; //ESC button
        //if(c==0x01) printf("Coordinates: %d %d",gfx_xpos(),gfx_ypos());
        
    }
    
    return 0;
}
