#include <stdio.h>

#include "../includes/dictionary.h"
#include "../includes/utils.h"
#include "../includes/defs.h"

void dict_show() {
    if (dictionary_size == 0) {
        printf("Dictionary is empty" N);
        printf("Press [2] to add your first word!" N);
    } else {
        int break_line = dictionary[0][0];
        printf(BOLD "DICTIONARY ENTRIES" N N RESET);
        for (int i = 0; i < dictionary_size; i++) {

            if (break_line != dictionary[i][0]) {
                break_line = dictionary[i][0];
                printf("\n");
            }

            printf("%d. %s\n", i + 1, dictionary[i]);


        }
    }

    press_enter_to_continue();
}
