
#include <stdlib.h>
#include "tictactoe.h"
#include "game.h"
#include "menu.h"

void play(){
    printf("Play\n");
}

void statistic(){
    printf("Statistic\n");
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
    int y_btn_margin = 75;

    char *play_msg = "  Play   ";
    char *stat_msg = "Statistic";

    Menu *start_menu = create_menu(2, 0, y_btn_margin);
    start_menu->buttons[0] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, play_msg, play); //Play button
    start_menu->buttons[1] = create_button(w, h, x_offset, y_offset, x_text_offset, y_text_offset, stat_msg, statistic); //Stats button
    

    return start_menu;
}

void check_menu_input(char c, Menu *m){
    if(c == 0x01) {
        int mouse_x = gfx_xpos();
        int mouse_y = gfx_ypos();

        for(int i=0; i < m->total_button; i++){
            Button b = *(m->buttons[i]);
            int min_x = b.x_offset;
            int max_x = min_x + b.w;
            int min_y = b.y_offset + m->y_btn_margin * (i - m->total_button + (i == m->total_button/2 && m->total_button%2 == 0));
            int max_y = min_y + b.h;
            
            if ((mouse_x >= min_x && mouse_x <= max_x ) && (mouse_y >= min_y && mouse_y <= max_y )){
                b.onclick();
            }

        }
    }
}