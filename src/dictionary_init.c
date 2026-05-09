#include <string.h>
#include <stdio.h>

#include "../includes/dictionary_sort.h"
#include "../includes/dictionary.h"
#include "../includes/utils.h"

int dict_init(void) {
    // If already initialized, clean up first
    if (dictionary != NULL) {
        cleanup();
    }

    dictionary = NULL;
    dictionary_size = 0;

    // Example: Load from file
    FILE *file = fopen("saves/dictionary.txt", "r");
    if (file == NULL) {
        // No file yet, start with empty dictionary
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) > 0) {
            char **tmp = realloc(dictionary, (dictionary_size + 1) * sizeof(char *));
            if (tmp == NULL) {
                fclose(file);
                cleanup();
                return -1;
            }
            dictionary = tmp;

            dictionary[dictionary_size] = malloc(strlen(line) + 1);
            if (dictionary[dictionary_size] == NULL) {
                fclose(file);
                cleanup();
                return -1;
            }

            strcpy(dictionary[dictionary_size], line);
            dictionary_size++;
        }
    }

    fclose(file);
    dict_sort();
    return 0;
}
