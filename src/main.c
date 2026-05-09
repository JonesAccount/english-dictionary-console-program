#include <stdio.h>

#include "../includes/dictionary_search.h"
#include "../includes/dictionary_init.h"
#include "../includes/dictionary_sort.h"
#include "../includes/dictionary_menu.h"
#include "../includes/dictionary_show.h"
#include "../includes/dictionary_save.h"
#include "../includes/dictionary_add.h"
#include "../includes/dictionary_del.h"
#include "../includes/dictionary.h"
#include "../includes/utils.h"

char **dictionary = NULL;
int dictionary_size = 0;

int main(void) {
    printf("\033[?25l");
    clear_screen();

    char ch;
    while (1) {
    	dict_init();
        dict_sort();
        dict_menu();
        ch = getch();

        if (ch) { clear_screen(); }

        switch (ch) {
            case '1':
                dict_show();
                break;
            case '2':
                if (dict_add() == -1) {
                    cleanup();
                    printf("\033[?25h");
                    return 1;
                }
                break;
            case '3':
                dict_search();
                break;
            case '4':
                dict_del();
                break;
            case '0':
                cleanup();
                printf("\033[?25h");
                return 0;
        }

        clear_screen();
        dict_save();
    }

    return 0;
}
