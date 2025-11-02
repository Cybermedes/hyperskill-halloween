#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_DIGITS 10

typedef struct DigitFrequency {
    char digit;
    int frequency;
} DigitFrequency;

void count_digit(DigitFrequency *freq, int value);

void sort_array(DigitFrequency *freq);

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117428238.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    DigitFrequency number_frequency[NUM_DIGITS];
    for (int i = 0; i < NUM_DIGITS; i++) {
        number_frequency[i].digit = (char)(48 + i);
        number_frequency[i].frequency = 0;
    }

    int ch = 0;
    int counter = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (!isdigit(ch)) {
            break;
        }

        count_digit(number_frequency, ch);
        counter++;
    }
    fclose(file);

    sort_array(number_frequency);

    printf("Result: ");
    for (int i = 0; i < 4; i++) {
        printf("%c", number_frequency[i].digit);
    }
    puts("");

    return 0;
}

void count_digit(DigitFrequency *freq, int value) {
    char digit = (char)value;
    for (int i = 0; i < NUM_DIGITS; i++) {
        if (freq[i].digit == digit) {
            freq[i].frequency += 1;
            break;
        }
    }
}

void sort_array(DigitFrequency *freq) {
    // Using bubble sort algorithm
    for (int i = 0; i < NUM_DIGITS - 1; i++) {
        for (int j = 0; j < NUM_DIGITS - i - 1; j++) {
            if (freq[j].frequency < freq[j + 1].frequency) {
                DigitFrequency temp = freq[j];
                freq[j] = freq[j + 1];
                freq[j + 1] = temp;
            }
        }
    }

    // If there are equal number of appearances, higher digit should come first
    for (int i = 0; i < NUM_DIGITS - 1; i++) {
        if (freq[i].frequency == freq[i + 1].frequency) {
            if (freq[i].digit < freq[i + 1].digit) {
                DigitFrequency temp = freq[i];
                freq[i] = freq[i + 1];
                freq[i + 1] = temp;
            }
        }
    }
}
