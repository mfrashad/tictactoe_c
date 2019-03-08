
#include <stdio.h>
#include "gfx.h"
#include "draw.h"
#include "menu.h"



void menu(){
    char c;
    Menu *start_menu = create_start_menu();
    draw_menu(start_menu);
    while(1){
        c = gfx_wait();
        check_menu_input(c, start_menu);
        if(c=='q') break;
    }
}

