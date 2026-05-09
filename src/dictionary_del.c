#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "../includes/dictionary_save.h"
#include "../includes/dictionary.h"
#include "../includes/utils.h"
#include "../includes/defs.h"

int dict_del(void) {
    if (dictionary_size == 0) {
        printf("Your dictionary is empty." N);
        printf("Press [2] to add your first word!" N);
    } else {
        char line[100];
        printf("Enter word to delete: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            press_enter_to_continue();
            return 0;
        }

        for (int i = 0; i < strlen(line); i++) {
            line[i] = tolower(line[i]);
        }
        line[0] = toupper(line[0]);

        int found = 0;
        int index = 0;
        for (int i = 0; i < dictionary_size; i++) {
            if (!strcmp(line, dictionary[i])) {
                found = 1;
                index = i;
                break;
            }
        }

        if (found) {
            free(dictionary[index]);

            for (int i = index; i < dictionary_size - 1; i++) {
                dictionary[i] = dictionary[i + 1];
            }

            dictionary_size--;

            if (dictionary_size > 0) {
                char **temp_memory = realloc(dictionary, dictionary_size * sizeof(char *));
                if (NULL == temp_memory) {
                    printf("Memory allocation error!" N);
                    cleanup();
                    return -1;
                }
                dictionary = temp_memory;
            } else {
                free(dictionary);
                dictionary = NULL;
            }

            dict_save();  // Auto-save after deleting
            printf(N "Word deleted successfully!" N);
        } else {
            printf(N "Word not found in dictionary." N);
        }
    }

    press_enter_to_continue();
    return 0;
}