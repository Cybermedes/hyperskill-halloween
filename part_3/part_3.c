#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26

typedef struct Letter {
    char character;
    int frequency;
    int first_index;
} Letter;

// Sort the array according to their order of appereance using bubble sort
void sort_array(Letter *array) {
    for (int i = 0; i < NUM_LETTERS - 1; i++) {
        for (int j = 0; j < NUM_LETTERS - i - 1; j++) {
            if (array[j].first_index > array[j + 1].first_index) {
                Letter temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

// Set initial values and letters for the array
void initialize_array(Letter *array) {
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        array[i].character = 'a' + i;
        array[i].frequency = 0;
        array[i].first_index = -1;
    }
}

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

    initialize_array(letters);

    char ch = 0;
    int counter = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n') {
        
        for (size_t i = 0; i < NUM_LETTERS; i++) {
            if (letters[i].character == ch) {
                letters[i].frequency += 1;
                
                if (letters[i].first_index == -1) {
                    letters[i].first_index = counter;
                }

                break;
            }
        }
        counter++;
    }
    fclose(file); // Close file

    sort_array(letters);

    printf("Result: ");
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        if (letters[i].frequency == 1) {
            printf("%c", letters[i].character);
        }
    }
    puts("");

    free(letters); // Free memory

    return 0;
}
