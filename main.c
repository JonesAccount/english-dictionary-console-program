#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>n
#include <ctype.h>

#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define N "\n"

char **dictionary = NULL;
int dictionary_size = 0;

static void interface(void);
static int add_word(void);
static void show_words(void);
static void sort_words(void);
static int search_word(void);
static int del_word(void);
static char getch(void);
static void clear_screen(void);
static void wait(void);
static void cleanup(void);

int main(void) {
    printf("\033[?25l");

    char ch;

    while (1) {
        sort_words();
        interface();
        ch = getch();

        if (ch) { clear_screen(); }

        switch (ch) {
            case '1':
                show_words();
                break;
            case '2':
                if (add_word() == -1) {
                    cleanup();
                    printf("\033[?25h");
                    return 1;
                }
                break;
            case '3':
                search_word();
                break;
            case '4':
                del_word();
                break;
            case '0':
                cleanup();
                printf("\033[?25h");
                return 0;
        }

        clear_screen();
    }

    return 0;
}

static void interface(void) {
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

static int add_word(void) {
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
        wait();
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

    wait();
    return 0;
}

static void show_words() {
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

    wait();
}

static void sort_words(void) {
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

static int search_word(void) {
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
            wait();
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

    wait();
    return 0;
}

static int del_word(void) {
    if (dictionary_size == 0) {
        printf("Dictionary is empty" N);
        printf("Press [2] to add your first word!" N);
    } else {
        char line[100];
        printf("Enter word to delete: ");

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return -1;
        }
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0) {
            wait();
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
            // Free the memory of the deleted word
            free(dictionary[index]);

            // Shift remaining words left
            for (int i = index; i < dictionary_size - 1; i++) {
                dictionary[i] = dictionary[i + 1];
            }

            dictionary_size--;

            // FIX: Only realloc if dictionary_size > 0
            if (dictionary_size > 0) {
                char **temp_memory = realloc(dictionary, dictionary_size * sizeof(char *));
                if (NULL == temp_memory) {
                    printf("Memory allocation error!" N);
                    cleanup();
                    return -1;
                }
                dictionary = temp_memory;
            } else {
                // If dictionary is empty, free the pointer completely
                free(dictionary);
                dictionary = NULL;
            }

            printf(N "Word deleted successfully!" N);
        }

        if (!found) {
            printf(N "Word not found in dictionary." N);
        }
    }

    wait();
    return 0;
}

static char getch(void) {
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

static void clear_screen(void) {
    fputs("\033[2J\033[H", stdout);
    fflush(stdout);
}

static void wait(void) {
    getch();
}

static void cleanup(void) {
    for (int i = 0; i < dictionary_size; i++) {
        free(dictionary[i]);
    }
    free(dictionary);
    dictionary = NULL;
    dictionary_size = 0;
}
