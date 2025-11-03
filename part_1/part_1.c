#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DIGITS 10

typedef struct Digit {
    char digit;
    int frequency;
} Digit;

void sort_array(Digit *freq);

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117428238.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    int ch = 0;
    int frequencies[64] = {0};
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != '\r') {
        if (isdigit(ch)) {
            frequencies[(int)ch]++;
        }
    }
    fclose(file);

    Digit number_frequency[NUM_DIGITS] = {0};
    for (int i = 0; i < NUM_DIGITS; i++) {
        number_frequency[i].digit = (char)(i + 48);
        number_frequency[i].frequency = frequencies[i + 48];
    }

    sort_array(number_frequency);

    printf("Result: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", number_frequency[i].digit);
    }
    puts("");

    return 0;
}

void sort_array(Digit *freq) {
    // Using bubble sort algorithm
    for (int i = 0; i < NUM_DIGITS - 1; i++) {
        for (int j = 0; j < NUM_DIGITS - i - 1; j++) {
            if (freq[j].frequency < freq[j + 1].frequency) {
                Digit temp = freq[j];
                freq[j] = freq[j + 1];
                freq[j + 1] = temp;
            }
        }
    }

    // If there are equal number of appearances, higher digit should come first
    for (int i = 0; i < NUM_DIGITS - 1; i++) {
        if (freq[i].frequency == freq[i + 1].frequency) {
            if (freq[i].digit < freq[i + 1].digit) {
                Digit temp = freq[i];
                freq[i] = freq[i + 1];
                freq[i + 1] = temp;
            }
        }
    }
}
