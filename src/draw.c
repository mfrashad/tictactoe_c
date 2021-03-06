#include "gfx.h"
#include "tictactoe.h"
#include "draw.h"
#include <stdio.h>
#include <stdbool.h>

extern int stat[2][TOTAL_SIZE][TOTAL_DATA];
extern bool keyboard_help;

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
            
            if(keyboard_help){
                int square_num = j+1 + i*game->size; //convert to num, start from 1
                char input = square_num + 96; //(a-z)
                gfx_text(&input, x_offset + SIDE_LENGTH * j + 5, y_offset + SIDE_LENGTH * i);
            }
            
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

        if(keyboard_help){
            char input = i+49;
            gfx_text(&input, rect_x + 10, text_y);
        }
        
    }
}

void draw_statistic(){
    int box1_w = WIN_WIDTH-60;
    int box1_h = 280;
    int box1_x = 30;
    int box1_y = 40;
    int box2_w = box1_w/2;
    int box2_h = box1_h - 30;
    int box2_x = box1_x;
    int box2_y = box1_y + 30;
    int text_y_margin = 30;
    char data[2][TOTAL_SIZE][TOTAL_DATA][5] = {0};
    char desc_single[6][20] = { "Games Played", "Games Draw", "Computer Won", "Computer Lost", "User Won", "User Lost"};
    char desc_multi[6][20] = { "Games Played", "Games Draw", "X Won", "X Lost", "O Won", "O Lost"};
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
    
    for(int i=0; i<6; i++) {
        gfx_text(desc_single[i], box2_x + 20, box2_y + 60 + i*text_y_margin);
    }
    
    for(int i=0; i<6; i++){
        int init_enum = i;
        if(i>=2) init_enum = i + COMPUTER_WON - 2;
        sprintf(data[SINGLE][SIZE_3][init_enum], "%2d", stat[SINGLE][SIZE_3][init_enum]);
        gfx_text(data[SINGLE][SIZE_3][init_enum], box2_x + box2_w - 50, box2_y + 60 + i*text_y_margin);
        draw_graph(box2_x + 200, box2_y + 60 + i*text_y_margin, 20, max_graph_length , stat[SINGLE][SIZE_3][init_enum], max_graph_val);
    }

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    
    for(int i=0;i<6;i++){
        gfx_text(desc_multi[i], box2_x + box2_w + 20, box2_y + 60 + 30*i);
    } 

    for(int i=0; i<6; i++){
        int init_enum = i;
        if(i>=2) init_enum = i + X_WON - 2;
        sprintf(data[MULTI][SIZE_3][init_enum], "%2d", stat[MULTI][SIZE_3][init_enum]);
        gfx_text(data[MULTI][SIZE_3][init_enum], box2_x + box2_w*2 - 50, box2_y + 60 + i*text_y_margin);
        draw_graph(box2_x + box2_w + 200, box2_y + 60 + i*30, 20, max_graph_length, stat[MULTI][SIZE_3][init_enum], max_graph_val);
    }

    //-------------------5x5------------------------------------//
    box1_y = box1_h + 40 + 30;
    box2_y = box1_y + 30;

    gfx_rectangle(box1_x, box1_y,box1_w, box1_h);
    gfx_text("5x5 Tic Tac Toe", box1_w/2 - 40, box1_y + 5);

    gfx_rectangle(box2_x, box2_y, box2_w, box2_h);
    gfx_text("1 Player", box2_x + box2_w/2 - 30, box2_y + 5);

    for(int i=0; i<6; i++) {
        gfx_text(desc_single[i], box2_x + 20, box2_y + 60 + i*text_y_margin);
    }

    for(int i=0; i<6; i++){
        int init_enum = i;
        if(i>=2) init_enum = i + COMPUTER_WON - 2;
        sprintf(data[SINGLE][SIZE_5][init_enum], "%2d", stat[SINGLE][SIZE_5][init_enum]);
        gfx_text(data[SINGLE][SIZE_5][init_enum], box2_x + box2_w - 50, box2_y + 60 + i*text_y_margin);
        draw_graph(box2_x + 200, box2_y + 60 + i*text_y_margin, 20, max_graph_length , stat[SINGLE][SIZE_5][init_enum], max_graph_val);
    }

    gfx_rectangle(box2_x + box2_w, box2_y, box2_w, box2_h);
    gfx_text("2 Player", box2_x + box2_w + box2_w/2 - 30, box2_y + 5);

    for(int i=0;i<6;i++){
        gfx_text(desc_multi[i], box2_x + box2_w + 20, box2_y + 60 + 30*i);
    }

    for(int i=0; i<6; i++){
        int init_enum = i;
        if(i>=2) init_enum = i + X_WON - 2;
        sprintf(data[MULTI][SIZE_5][init_enum], "%2d", stat[MULTI][SIZE_5][init_enum]);
        gfx_text(data[MULTI][SIZE_5][init_enum], box2_x + box2_w*2 - 50, box2_y + 60 +  i*text_y_margin);
        draw_graph(box2_x + box2_w + 200, box2_y + 60 + i*30, 20, max_graph_length, stat[MULTI][SIZE_5][init_enum], max_graph_val);
    }
}

void draw_title(){
    int start_x = WIN_WIDTH/2 - 500;
    int start_y = 50;
    int weight = 20;
    //draw_char('t', start_x, start_y, weight);
    draw_string("tic tac toe", start_x, start_y, weight);
}

void draw_string(char *str, int x, int y, int weight){
    int i=0;
    while(str[i]!='\0'){
        draw_char(str[i], x+i*90, y, 20);
        i++;
    }
}

void draw_char(char c, int x, int y, int weight){
    switch(c){
        case 't':
            gfx_fillrectangle(x,y,80,weight);
            gfx_fillrectangle(x+(80-weight)/2, y+weight, weight, 80-weight);
            break;
        case 'i':
            gfx_fillrectangle(x+(80-weight)/2,y,weight, 80);
            break;
        case 'c':
            gfx_fillrectangle(x,y,80,weight);
            gfx_fillrectangle(x,y+weight,weight,80-2*weight);
            gfx_fillrectangle(x,y+80-weight,80,weight);
            break;
        case 'a':
            gfx_fillrectangle(x,y,weight,80);
            gfx_fillrectangle(x+weight,y,80-2*weight,weight);
            gfx_fillrectangle(x+weight,y+2*weight,80-2*weight,weight);
            gfx_fillrectangle(x+80-weight,y,weight,80);
            break;
        case 'o':
            gfx_fillrectangle(x,y,80,weight);
            gfx_fillrectangle(x,y+weight,weight,80-2*weight);
            gfx_fillrectangle(x+80-weight,y+weight,weight,80-2*weight);
            gfx_fillrectangle(x,y+80-weight,80,weight);
            break;
        case 'e':
            gfx_fillrectangle(x,y,weight,80);
            gfx_fillrectangle(x+weight,y,80-weight,weight);
            gfx_fillrectangle(x+weight,y+weight+(80-3*weight)/2,80-weight,weight);
            gfx_fillrectangle(x+weight,y+80-weight,80-weight,weight);
        case ' ':
            break;
    }
}

void draw_graph(int x, int y, int width, int max_length, int value, int max_value){
    gfx_color(255,255,255);
    float length = (float)value/max_value * max_length + 1;
    gfx_fillrectangle(x, y, (int)length, width);
}

void draw_win_text(Player winner){
    char *str;
    if(winner==O) str = "Player O wins!";
    if(winner==X) str = "Player X wins!";
    if(winner==NONE) str = "   Draw!   ";
    gfx_text(str, WIN_WIDTH/2 - 80, 60);
}

void draw_game_text(Game *game){
    char *str;
    str = (game->next_turn == O) ? "Player O's turn" : "Player X's turn";  
    gfx_text(str, WIN_WIDTH/2 - 80, 50);
}

void draw_keyboard_help_text(){
    char msg[100] = "       Press TAB for keyboard input help      ";
    if(keyboard_help) sprintf(msg, "Press the key shown inside the button to click the area");
    gfx_text(msg, WIN_WIDTH/2 - 300, WIN_HEIGHT - 50);
}