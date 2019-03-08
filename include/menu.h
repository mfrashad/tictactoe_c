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

Button *create_button(int w, int h, int x_offset, int y_offset, int x_text_offset, int y_text_offset, char *msg, void (*onclick)());

Menu *create_menu(int total_button, int x_btn_margin, int y_btn_margin);

Menu *create_start_menu();

#endif