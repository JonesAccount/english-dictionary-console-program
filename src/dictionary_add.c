#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../includes/dictionary.h"
#include "../includes/utils.h"
#include "../includes/defs.h"

int dict_add(void) {
    char line[100];
    
    int check_word_no = 1;
    printf("Enter a new word: ");
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        clear_screen();
        check_word_no = 0;
    }

    for (int i = 0; i < strlen(line); i++) { line[i] = tolower(line[i]); }
    line[0] = toupper(line[0]);

    for (int i = 0; i < strlen(line); i++) {
        if (!isalpha(line[i])) {
            check_word_no = 0;
            break;
        }
    }

    if (strlen(line) < 2) { check_word_no = 0; }

    // Check if word already exists
    int already_exists = 0;
    for (int i = 0; i < dictionary_size; i++) {
        if (strcmp(line, dictionary[i]) == 0) {
            already_exists = 1;
            break;
        }
    }

    if (already_exists) {
        printf(N "Word already exists in dictionary!" N);
        press_enter_to_continue();
        return 0;
    }

    if (check_word_no) {
        char **tmp = realloc(dictionary, (dictionary_size + 1) * sizeof(char *));
        if (NULL == tmp) {
            cleanup();
            return -1;
        }
        dictionary = tmp;

        dictionary[dictionary_size] = malloc(strlen(line) + 1);
        if (NULL == dictionary[dictionary_size]) {
            cleanup();
            return -1;
        }

        strcpy(dictionary[dictionary_size], line);
        dictionary_size++;

        printf(N "Word added successfully!");
    } else {
        printf(N "Invalid word! Requirements:");
        printf(N "- Letters only (A-Z)");
        printf(N "- Minimum 2 characters");
    }

    press_enter_to_continue();
    return 0;
}
