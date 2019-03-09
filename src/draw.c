#include "gfx.h"
#include "tictactoe.h"
#include "draw.h"




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

    gfx_color(255,255,255);
    for(int i = 0; i < game->size; i++) {
        for(int j = 0; j < game->size; j++){
            gfx_rectangle(x_offset + SIDE_LENGTH * j, y_offset + SIDE_LENGTH * i, SIDE_LENGTH, SIDE_LENGTH);
            if (game->board[i][j] == X) draw_x(x_offset + 10 + SIDE_LENGTH * j, y_offset + 10 + SIDE_LENGTH * i, SIDE_LENGTH - 20);
            if (game->board[i][j] == O) draw_o(x_offset + 10 + SIDE_LENGTH * j, y_offset + 10 + SIDE_LENGTH * i, SIDE_LENGTH - 20);
        }
    }
}

void draw_menu(Menu *m){

    for(int i=0; i < m->total_button; i++){
        Button b = *(m->buttons[i]);
        gfx_rectangle(b.x_offset, b.y_offset + m->y_btn_margin * (i - m->total_button/2 + (i == m->total_button/2 && m->total_button%2 == 0)), b.w, b.h);
        gfx_text(b.msg, b.x_offset + b.w/2 - b.x_text_offset, b.y_offset + b.h/2 + m->y_btn_margin * (i - m->total_button/2 + (i == m->total_button/2 && m->total_button%2 == 0)) - b.y_text_offset);
    }
}

void draw_win_text(Player winner){
    char *str;
    if(winner==O) str = "Player O wins";
    if(winner==X) str = "Player X wins";
    gfx_text(str, 200, 100);
}