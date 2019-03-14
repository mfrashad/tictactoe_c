#include "gfx.h"
#include "tictactoe.h"
#include "draw.h"
#include <stdio.h>

extern int stat[2][TOTAL_SIZE][TOTAL_DATA];

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
    int box1_h = 250;
    int box1_x = 30;
    int box1_y = 40;
    int box2_w = box1_w/2;
    int box2_h = box1_h - 30;
    int box2_x = box1_x;
    int box2_y = box1_y + 30;
    int text_y_margin = 30;
    char data[2][TOTAL_SIZE][TOTAL_DATA][5] = {0};
    char desc_single[5][20] = { "Games Played", "Computer Won", "User Lost", "User Won", "Uer Lost"};
    char desc_multi[5][20] = { "Games Played", "X Won", "X Lost", "O Won", "O Lost"};
    int max_graph_length = 310;
    int max_graph_val = 1;
    for(int i=0;i<TOTAL_SIZE; i++) {
        for(int j=0;j<2;j++) {
            if(stat[i][j][GAMES_PLAYED] > max_graph_val) max_graph_val = stat[i][j][GAMES_PLAYED];
        }
    }

    gfx_text("Statistic", WIN_WIDTH/2 - 30, 5);
    gfx_rectangle(box1_x, box1_y,box1_w, box1_h);
    gfx_text("3x3 Tic Tac Toe", box1_w/2 - 40, box1_y + 5);

    gfx_rectangle(box2_x, box2_y, box2_w, box2_h);
    gfx_text("1 Player", box2_x + box2_w/2 - 30, box2_y + 5);
    
    for(int i=0; i<5; i++) {
        gfx_text(desc_single[i], box2_x + 20, box2_y + 60 + i*text_y_margin);
        //gfx_text(":", box2_x + 200, box2_y + 60 + i*text_y_margin);
    }
    
    sprintf(data[SINGLE][SIZE_3][GAMES_PLAYED], "%2d", stat[SINGLE][SIZE_3][GAMES_PLAYED]);
    gfx_text(data[SINGLE][SIZE_3][GAMES_PLAYED], box2_x + box2_w - 50, box2_y + 60);
    draw_graph(box2_x + 200, box2_y + 60, 20, max_graph_length, stat[SINGLE][SIZE_3][GAMES_PLAYED], max_graph_val);
    for(int i=0; i<4; i++){
        int init_enum = i + COMPUTER_WON;
        sprintf(data[SINGLE][SIZE_3][init_enum], "%2d", stat[SINGLE][SIZE_3][init_enum]);
        gfx_text(data[SINGLE][SIZE_3][init_enum], box2_x + box2_w - 50, box2_y + 60 + (i+1)*text_y_margin);
        draw_graph(box2_x + 200, box2_y + 60 + (i+1)*text_y_margin, 20, max_graph_length , stat[SINGLE][SIZE_3][init_enum], max_graph_val);
    }

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    
    for(int i=0;i<5;i++){
        gfx_text(desc_multi[i], box2_x + box2_w + 20, box2_y + 60 + 30*i);
        //gfx_text(":", box2_x + box2_w + 200, box2_y + 60 + i*30);
    } 

    sprintf(data[MULTI][SIZE_3][GAMES_PLAYED], "%2d", stat[MULTI][SIZE_3][GAMES_PLAYED]);
    gfx_text(data[MULTI][SIZE_3][GAMES_PLAYED], box2_x + box2_w*2 - 50, box2_y + 60);
    draw_graph(box2_x + box2_w + 200, box2_y + 60, 20, max_graph_length, stat[MULTI][SIZE_3][GAMES_PLAYED], max_graph_val);
    for(int i=0; i<4; i++){
        int init_enum = i + X_WON;
        sprintf(data[MULTI][SIZE_3][init_enum], "%2d", stat[MULTI][SIZE_3][init_enum]);
        gfx_text(data[MULTI][SIZE_3][init_enum], box2_x + box2_w*2 - 50, box2_y + 60 + (i+1)*text_y_margin);
        draw_graph(box2_x + box2_w + 200, box2_y + 60 + (i+1)*30, 20, max_graph_length, stat[MULTI][SIZE_3][init_enum], max_graph_val);
    }

    //-------------------5x5------------------------------------//
    box1_y = box1_h + 40 + 30;
    box2_y = box1_y + 30;

    gfx_rectangle(box1_x, box1_y,box1_w, box1_h);
    gfx_text("5x5 Tic Tac Toe", box1_w/2 - 40, box1_y + 5);

    gfx_rectangle(box2_x, box2_y, box2_w, box2_h);
    gfx_text("1 Player", box2_x + box2_w/2 - 30, box2_y + 5);

    for(int i=0; i<5; i++) {
        gfx_text(desc_single[i], box2_x + 20, box2_y + 60 + i*text_y_margin);
        //gfx_text(":", box2_x + 200, box2_y + 60 + i*text_y_margin);
    }

    sprintf(data[SINGLE][SIZE_5][GAMES_PLAYED], "%2d", stat[SINGLE][SIZE_5][GAMES_PLAYED]);
    gfx_text(data[SINGLE][SIZE_5][GAMES_PLAYED], box2_x + box2_w - 50, box2_y + 60);
    draw_graph(box2_x + 200, box2_y + 60, 20, max_graph_length, stat[SINGLE][SIZE_5][GAMES_PLAYED], max_graph_val);
    for(int i=0; i<4; i++){
        int init_enum = i + COMPUTER_WON;
        sprintf(data[SINGLE][SIZE_5][init_enum], "%2d", stat[SINGLE][SIZE_5][init_enum]);
        gfx_text(data[SINGLE][SIZE_5][init_enum], box2_x + box2_w - 50, box2_y + 60 + (i+1)*text_y_margin);
        draw_graph(box2_x + 200, box2_y + 60 + (i+1)*text_y_margin, 20, max_graph_length , stat[SINGLE][SIZE_5][init_enum], max_graph_val);
    }

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    for(int i=0;i<5;i++){
        gfx_text(desc_multi[i], box2_x + box2_w + 20, box2_y + 60 + 30*i);
        //gfx_text(":", box2_x + box2_w + 200, box2_y + 60 + i*30);
    }

    sprintf(data[MULTI][SIZE_5][GAMES_PLAYED], "%2d", stat[MULTI][SIZE_5][GAMES_PLAYED]);
    gfx_text(data[MULTI][SIZE_5][GAMES_PLAYED], box2_x + box2_w*2 - 50, box2_y + 60);
    draw_graph(box2_x + box2_w + 200, box2_y + 60, 20, max_graph_length, stat[MULTI][SIZE_3][GAMES_PLAYED], max_graph_val);
    for(int i=0; i<4; i++){
        int init_enum = i + X_WON;
        sprintf(data[MULTI][SIZE_5][init_enum], "%2d", stat[MULTI][SIZE_5][init_enum]);
        gfx_text(data[MULTI][SIZE_5][init_enum], box2_x + box2_w*2 - 50, box2_y + 60 + (i+1)*text_y_margin);
        draw_graph(box2_x + box2_w + 200, box2_y + 60 + (i+1)*30, 20, max_graph_length, stat[MULTI][SIZE_5][init_enum], max_graph_val);
    }
}

void draw_graph(int x, int y, int width, int max_length, int value, int max_value){
    gfx_color(255,255,255);
    float length = (float)value/max_value * max_length + 1;
    gfx_fillrectangle(x, y, (int)length, width);
}

void draw_win_text(Player winner){
    char *str;
    if(winner==O) str = "Player O wins";
    if(winner==X) str = "Player X wins";
    if(winner==NONE) str = "   Draw!   ";
    gfx_text(str, WIN_WIDTH/2 - 60, 50);
}

void draw_game_text(Game *game){
    char *str;
    str = (game->next_turn == O) ? "Player O's turn" : "Player X's turn";  
    gfx_text(str, WIN_WIDTH/2 - 60, 50);
}