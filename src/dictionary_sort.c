#include <string.h>

#include "../includes/dictionary.h"

void dict_sort(void) {
    if (dictionary_size <= 1 || dictionary == NULL) return;

    char *tmp;

    for (int i = 0; i < dictionary_size - 1; i++) {
        for (int j = 0; j < dictionary_size - i - 1; j++) {
            if (strcmp(dictionary[j], dictionary[j+1]) > 0) {
                tmp = dictionary[j];
                dictionary[j] = dictionary[j+1];
                dictionary[j+1] = tmp;
            }
        }
    }
}
