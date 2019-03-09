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
        int margin_factor = (i - m->total_button/2 + (i == m->total_button/2 && m->total_button%2 == 0));
        int rect_x = b.x_offset + m->x_btn_margin * margin_factor;
        int rect_y = b.y_offset + m->y_btn_margin * margin_factor;
        int text_x = b.x_offset + b.w/2 + m->x_btn_margin * margin_factor - b.x_text_offset;
        int text_y = b.y_offset + b.h/2 + m->y_btn_margin * margin_factor - b.y_text_offset;
        gfx_rectangle(rect_x, rect_y, b.w, b.h);
        gfx_text(b.msg, text_x, text_y);
    }
}

void draw_statistic(){
    int box1_w = WIN_WIDTH-60;
    int box1_h = 300;
    int box1_x = 30;
    int box1_y = 40;
    int box2_w = box1_w/2;
    int box2_h = box1_h - 30;
    int box2_x = box1_x;
    int box2_y = box1_y + 30;
    gfx_text("Statistic", WIN_WIDTH/2 - 30, 5);
    gfx_rectangle(box1_x, box1_y,box1_w, box1_h);
    gfx_text("3x3 Tic Tac Toe", box1_w/2 - 40, box1_y + 5);

    gfx_rectangle(box2_x, box2_y, box2_w, box2_h);
    gfx_text("1 Player", box2_x + box2_w/2 - 30, box2_y + 5);
    
    gfx_text("Games Played", box2_x + 20, box2_y + 60);
    gfx_text("Computer Won", box2_x + 20, box2_y + 100);
    gfx_text("Computer Lost", box2_x + 20, box2_y + 140);
    gfx_text("User Won", box2_x + 20, box2_y + 180);
    gfx_text("User Lost", box2_x + 20, box2_y + 220);

    for(int i=0; i<5; i++) gfx_text(":", box2_x + 200, box2_y + 60 + i*40);

    gfx_text("13", box2_x + box2_w - 50, box2_y + 60);
    gfx_text(" 3", box2_x + box2_w - 50, box2_y + 100);
    gfx_text("10", box2_x + box2_w - 50, box2_y + 140);
    gfx_text("10", box2_x + box2_w - 50, box2_y + 180);
    gfx_text(" 3", box2_x + box2_w - 50, box2_y + 220);

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    gfx_text("Games Played", box2_x + box2_w + 20, box2_y + 60);
    gfx_text("Computer Won", box2_x + box2_w + 20, box2_y + 100);
    gfx_text("Computer Lost", box2_x + box2_w + 20, box2_y + 140);
    gfx_text("User Won", box2_x + box2_w + 20, box2_y + 180);
    gfx_text("User Lost", box2_x + box2_w + 20, box2_y + 220);

    for(int i=0; i<5; i++) gfx_text(":", box2_x + box2_w + 200, box2_y + 60 + i*40);

    gfx_text("13", box2_x + box2_w*2 - 50, box2_y + 60);
    gfx_text(" 3", box2_x + box2_w*2 - 50, box2_y + 100);
    gfx_text("10", box2_x + box2_w*2 - 50, box2_y + 140);
    gfx_text("10", box2_x + box2_w*2 - 50, box2_y + 180);
    gfx_text(" 3", box2_x + box2_w*2 - 50, box2_y + 220);


    box1_y = box1_h + 40 + 30;
    box2_y = box1_y + 30;

    gfx_rectangle(box1_x, box1_y,box1_w, box1_h);
    gfx_text("5x5 Tic Tac Toe", box1_w/2 - 40, box1_y + 5);

    gfx_rectangle(box2_x, box2_y, box2_w, box2_h);
    gfx_text("1 Player", box2_x + box2_w/2 - 30, box2_y + 5);
    
    gfx_text("Games Played", box2_x + 20, box2_y + 60);
    gfx_text("Computer Won", box2_x + 20, box2_y + 100);
    gfx_text("Computer Lost", box2_x + 20, box2_y + 140);
    gfx_text("User Won", box2_x + 20, box2_y + 180);
    gfx_text("User Lost", box2_x + 20, box2_y + 220);

    for(int i=0; i<5; i++) gfx_text(":", box2_x + 200, box2_y + 60 + i*40);

    gfx_text("13", box2_x + box2_w - 50, box2_y + 60);
    gfx_text(" 3", box2_x + box2_w - 50, box2_y + 100);
    gfx_text("10", box2_x + box2_w - 50, box2_y + 140);
    gfx_text("10", box2_x + box2_w - 50, box2_y + 180);
    gfx_text(" 3", box2_x + box2_w - 50, box2_y + 220);

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    gfx_text("Games Played", box2_x + box2_w + 20, box2_y + 60);
    gfx_text("Computer Won", box2_x + box2_w + 20, box2_y + 100);
    gfx_text("Computer Lost", box2_x + box2_w + 20, box2_y + 140);
    gfx_text("User Won", box2_x + box2_w + 20, box2_y + 180);
    gfx_text("User Lost", box2_x + box2_w + 20, box2_y + 220);

    for(int i=0; i<5; i++) gfx_text(":", box2_x + box2_w + 200, box2_y + 60 + i*40);

    gfx_text("13", box2_x + box2_w*2 - 50, box2_y + 60);
    gfx_text(" 3", box2_x + box2_w*2 - 50, box2_y + 100);
    gfx_text("10", box2_x + box2_w*2 - 50, box2_y + 140);
    gfx_text("10", box2_x + box2_w*2 - 50, box2_y + 180);
    gfx_text(" 3", box2_x + box2_w*2 - 50, box2_y + 220);
}

void draw_win_text(Player winner){
    char *str;
    if(winner==O) str = "Player O wins";
    if(winner==X) str = "Player X wins";
    gfx_text(str, WIN_WIDTH/2 - 60, 100);
}