#ifndef MENU_H
#define MENU_H

typedef struct {
    int w;
    int h;;
    int x_offset;
    int y_offset;
    int x_text_offset;
    int y_text_offset;
    char *msg;
    void (*onclick)();
} Button;

typedef struct {
    Button **buttons;
    int total_button;
    int x_btn_margin;
    int y_btn_margin;
} Menu;

typedef enum {
    MAIN_MENU,
    MODE_MENU,
    PLAYER_MENU,
    STATISTIC,
    GAME1,
    GAME2,
    GAME_WIN
} GameState;

Button *create_button(int w, int h, int x_offset, int y_offset, int x_text_offset, int y_text_offset, char *msg, void (*onclick)());

Menu *create_menu(int total_button, int x_btn_margin, int y_btn_margin);

Menu *create_start_menu();

Menu *create_mode_menu();

Menu *create_win_menu(Game *game);

void check_menu_input(char c, Menu *m);

void play();
void statistic();

#endif