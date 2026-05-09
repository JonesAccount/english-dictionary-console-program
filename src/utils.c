#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "../includes/dictionary.h"

void clear_screen(void) { fputs("\033[2J\033[H", stdout); fflush(stdout); }

void cleanup(void) {
    for (int i = 0; i < dictionary_size; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
    dictionary = NULL;
    dictionary_size = 0;
}

char getch(void) {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void press_enter_to_continue(void) { getch(); }