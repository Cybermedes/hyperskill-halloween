#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117443619.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    size_t buff_size = 1024;
    char *sequence = calloc(buff_size, sizeof(char));
    if (sequence == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    int character = 0;
    size_t counter = 0;
    
    while ((character = fgetc(file)) != EOF) {
        if (counter + 1 >= buff_size) { // Leave room for the '\0'
            buff_size *= 2; // Increase buffer size if necessary
            char *temp = realloc(sequence, buff_size * sizeof(char));
            if (temp == NULL) {
                perror("Failed to reallocate memory");
                fclose(file);
                free(sequence);
                return EXIT_FAILURE;
            }

            sequence = temp;
        }

        // Don't the newline character
        if (character == '\n') {
            break;
        }

        sequence[counter++] = (char)character;
    }

    sequence[counter] = '\0';
    fclose(file);

    int result = 0;
    int degrees = 0;
    char *token = strtok(sequence, ",");
    
    while (token != NULL) {
        
        degrees = (int)strtol(token, NULL, 10);
        result += degrees;

        if (result > 360) {
            result -= 360;
        } else if (result < 0) {
            result += 360;
        }

        token = strtok(NULL, ",");
    }

    free(sequence);
    printf("Result: %d\n", result);

    return 0;
}
