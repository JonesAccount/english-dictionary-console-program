#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../includes/dictionary.h"
#include "../includes/utils.h"
#include "../includes/defs.h"

int dict_search(void) {
    if (dictionary_size == 0) {
        printf("Dictionary is empty" N);
        printf("Press [2] to add your first word!" N);
    } else {
        char line[100];
        printf("Search for a word: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            press_enter_to_continue();
            return 0;
        }

        for (int i = 0; i < strlen(line); i++) { line[i] = tolower(line[i]); }
        line[0] = toupper(line[0]);

        int found = 0;
        for (int i = 0; i < dictionary_size; i++) {
            if (!strcmp(line, dictionary[i])) {
                printf(N "Word found: %s", dictionary[i]);
                found = 1;
                break;
            }
        }

        if (!found) { printf(N "Word not found in dictionary."); }
    }

    press_enter_to_continue();
    return 0;
}
