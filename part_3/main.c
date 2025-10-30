#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26

typedef struct Letter {
    char character;
    int frequency;
    int first_index;
} Letter;

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117460572.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    Letter *letters = malloc(NUM_LETTERS * sizeof(Letter));
    if (letters == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < NUM_LETTERS; i++) {
        letters[i].character = 'a' + i;
        letters[i].frequency = 0;
        letters[i].first_index = 0;
    }

    char ch = 0;
    int counter = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            break;
        }

        for (size_t i = 0; i < NUM_LETTERS; i++) {
            if (letters[i].character == ch) {
                letters[i].frequency += 1;
                letters[i].first_index = counter;
                break;
            }
        }
        counter++;
    }
    fclose(file); // Close file

    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (letters[i].frequency == 1) {
            printf("%c: %d\n", letters[i].character, letters[i].first_index);
        }
    }

    free(letters); // Free memory

    return 0;
}
