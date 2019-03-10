
#include <stdlib.h>
#include <stdio.h>
#include "gfx.h"
#include "tictactoe.h"
#include "game.h"
#include "menu.h"
#include "draw.h"

extern GameState game_state;
extern Game *game;
void main_menu() {
    game_state = MAIN_MENU;
}
void play(){
    game_state = SIZE_MENU;
}

void select_5(){
    game_state = MODE_MENU;
    resize(&game, 5);
}

void select_3(){
    game_state = MODE_MENU;
    resize(&game, 3);
}

void play1(){
    reset(&game);
    game_state = PLAYER_MENU;
    game->mode = SINGLE;
}

void select_o(){
    game_state = GAME1;
    game->player = O;
}

void select_x(){
    game_state = GAME1;
    game->player = X;
}

void play2(){
    reset(&game);
    game_state = GAME2;
    game->mode = MULTI;
}

void statistic(){
    game_state = STATISTIC;
}

void quit(){
    game_state = QUIT;
}

Button *create_button(int w, int h, int x_offset, int y_offset, int x_text_offset, int y_text_offset, char *msg, void (*onclick)()) {
    Button *b = malloc(sizeof(Button));
    b->w = w;
    b->h = h;
    b->x_offset = x_offset;
    b->y_offset = y_offset;
    b->x_text_offset = x_text_offset;
    b->y_text_offset = y_text_offset;
    b->msg = msg;
    b->onclick = onclick;
    return b;
}

Menu *create_menu(int total_button, int x_btn_margin, int y_btn_margin) {
    Menu *m = malloc(sizeof(Menu));
    m->total_button = total_button;
    m->buttons = malloc(total_button * sizeof(Button*));
    for(int i=0; i < total_button; i++) m->buttons[i] = malloc(sizeof(Button));
    m->x_btn_margin = x_btn_margin;
    m->y_btn_margin = y_btn_margin;

    return m;
}

Menu *create_start_menu(){
    int w = 300, h = 100;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = (WIN_HEIGHT - h) / 2;
    int x_text_offset = 40;
    int y_text_offset = 10;
    int y_btn_margin = 120;

    char *play_msg = "  Play   ";
    char *stat_msg = "Statistic";
    char *quit_msg = "  Quit   ";

    Menu *start_menu = create_menu(3, 0, y_btn_margin);
    start_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, play_msg, play); //Play button
    start_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, stat_msg, statistic); //Stats button
    start_menu->buttons[2] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, quit_msg, quit); //Quit button
    

    return start_menu;
}

Menu *create_size_menu(){
    int w = 300, h = 100;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = (WIN_HEIGHT - h) / 2;
    int x_text_offset = 25;
    int y_text_offset = 10;
    int y_btn_margin = 120;

    char *msg1 = "3 x 3";
    char *msg2 = "5 x 5";
    char *back_msg = "Back";

    Menu *mode_menu = create_menu(3, 0, y_btn_margin);
    mode_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg1, select_3); //Play button
    mode_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg2, select_5); //Stats button
    mode_menu->buttons[2] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, back_msg, main_menu); //Back button
    return mode_menu;
}

Menu *create_mode_menu(){
    int w = 300, h = 100;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = (WIN_HEIGHT - h) / 2;
    int x_text_offset = 40;
    int y_text_offset = 10;
    int y_btn_margin = 120;

    char *msg1 = "1 Player";
    char *msg2 = "2 Player";
    char *back_msg = "  Back  ";

    Menu *mode_menu = create_menu(3, 0, y_btn_margin);
    mode_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg1, play1); //Play button
    mode_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg2, play2); //Stats button
    mode_menu->buttons[2] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, back_msg, main_menu); //Back button
    return mode_menu;
}

Menu *create_player_menu(){
    int w = 300, h = 100;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = (WIN_HEIGHT - h) / 2;
    int x_text_offset = 40;
    int y_text_offset = 10;
    int y_btn_margin = 120;

    char *msg1 = "Play as X";
    char *msg2 = "Play as O";
    char *back_msg = "  Back  ";

    Menu *player_menu = create_menu(3, 0, y_btn_margin);
    player_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg1, select_x); //Play button
    player_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg2, select_o); //Stats button
    player_menu->buttons[2] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, back_msg, main_menu); //Back button
    return player_menu;
}

Menu *create_win_menu(Game *game){
    int w = 180, h = 60;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = 680;
    int x_text_offset = 40;
    int y_text_offset = 10;
    int x_btn_margin = 120;

    char *msg1 = "Play Again";
    char *msg2 = "Main Menu ";

    Menu *win_menu = create_menu(2, x_btn_margin, 0);
    win_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg1, game->mode == SINGLE ? play1 : play2); //Play button
    win_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, msg2, main_menu); //Stats button
    return win_menu;
}

Menu *create_statistic_menu(){
    int w = 150, h = 40;
    int x_offset = (WIN_WIDTH - w) / 2;
    int y_offset = 700;
    int x_text_offset = 20;
    int y_text_offset = 10;
    int x_btn_margin = 120;

    char *back_msg = "Back";

    Menu *statistic_menu = create_menu(1, x_btn_margin, 0);
    statistic_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, back_msg, main_menu); //Play button
    return statistic_menu;
}


bool check_menu_input(char c, Menu *m){
    if(c == 0x01) {
        int mouse_x = gfx_xpos();
        int mouse_y = gfx_ypos();

        for(int i=0; i < m->total_button; i++){
            Button b = *(m->buttons[i]);
            int margin_factor = (i - m->total_button/2 + (i == m->total_button/2 && m->total_button%2 == 0));
            int min_x = b.x_offset + m->x_btn_margin * margin_factor;
            int max_x = min_x + b.w;
            int min_y = b.y_offset + m->y_btn_margin * margin_factor;
            int max_y = min_y + b.h;
            
            if ((mouse_x >= min_x && mouse_x <= max_x ) && (mouse_y >= min_y && mouse_y <= max_y )){
                b.onclick();
                return true;
            }

        }
    }
    return false;
}