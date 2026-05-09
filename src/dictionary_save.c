#include <stdio.h>

#include "../includes/dictionary_sort.h"
#include "../includes/dictionary.h"
#include "../includes/defs.h"

int dict_save(void) {
    FILE *file = fopen("saves/dictionary.txt", "w");
    if (file == NULL) {
        printf(N "Error: Could not save dictionary!" N);
        return -1;
    }

    // Sort before saving to keep file organized
    dict_sort();

    for (int i = 0; i < dictionary_size; i++) {
        fprintf(file, "%s\n", dictionary[i]);
    }

    fclose(file);
    return 0;
}
