#include "menu.h"
#include "tictactoe.h"
#ifndef DRAW_H
#define DRAW_H

void draw_x(int x, int y, int w);

void draw_o(int x, int y, int w);

void draw_board(Game *game);

void draw_menu(Menu *menu);

void draw_win_text(Player winner);

void draw_graph(int x, int y, int width, int max_length, int value);

void draw_statistic();

#endif