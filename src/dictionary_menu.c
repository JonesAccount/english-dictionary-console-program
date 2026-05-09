#include <stdio.h>

#include "../includes/dictionary.h"
#include "../includes/defs.h"

void dict_menu(void) {
    printf(BOLD RED "\033[0;9HENGLISH DICTIONARY" N N RESET);

    printf(BOLD "::MENU" RESET N);
    printf("[1] Browse Dictionary" N);
    printf("[2] Add New Word" N);
    printf("[3] Search Words" N);
    printf("[4] Delete Word" N);
    printf("[0] Quit" N N);

    for (int i = 0; i < 30; i++) {
        printf("─");
    }
    printf(N);

    printf(BOLD "::SUMMARY" RESET N);
    printf("Total Words: %d" N N, dictionary_size);
    printf(BOLD "Words by Letter" RESET N);
    int letter_count[26] = {0};

	for (int i = 0; i < dictionary_size; i++) {
	    if (dictionary[i] && dictionary[i][0] >= 'A' && dictionary[i][0] <= 'Z') {
	        letter_count[dictionary[i][0] - 'A']++;
	    }
	}
	
	for (int i = 0; i < 26; i++) {
	    printf(YELLOW "%c" RESET ": %-2d  ", 'A' + i, letter_count[i]);
	    if ((i + 1) % 4 == 0) { printf(N); }
	}
	
}
	
	
