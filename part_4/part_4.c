#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char KEYPAD[4][4] = {{'A', 'B', 'C', 'D'},
                           {'E', 'F', 'G', 'H'},
                           {'I', 'J', 'K', 'L'},
                           {'M', 'N', 'O', 'P'}};

void strip_newline(char *text) {
    for (size_t i = 0; i < strlen(text); i++) {
        if (text[i] == '\n') {
            text[i] = '\0';
        }
    }
}

char get_letter_from_keypad(char *directions) {
    int x = 0, y = 0;

    char *tok = strtok(directions, ",");

    while (tok != NULL) {
        
        strip_newline(tok); // strip '\n' from tokens
        
        if (strcmp(tok, "UP") == 0) {
            if (y > 0)
                y -= 1;
        } else if (strcmp(tok, "DOWN") == 0) {
            if (y < 3)
                y += 1;
        } else if (strcmp(tok, "RIGHT") == 0) {
            if (x < 3)
                x += 1;
        } else if (strcmp(tok, "LEFT") == 0) {
            if (x > 0)
                x -= 1;
        }

        tok = strtok(NULL, ",");
    }

    return KEYPAD[y][x];
}

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117566097.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    size_t buffer_size = 2 * 1024;
    char *buffer = calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    int ch = 0;
    while ((fgets(buffer, buffer_size - 1, file)) != NULL) {
        buffer[buffer_size - 1] = '\0';
        ch = get_letter_from_keypad(buffer);
        if (ch == EOF) {
            fclose(file);
            free(buffer);
            return EXIT_FAILURE;
        }

        printf("%c", ch);
        memset(buffer, 0, buffer_size); // Clean buffer
    }
    printf("A\n"); // Last empty line from the file

    fclose(file); // Close file

    free(buffer); // Free allocated memory

    return 0;
}
