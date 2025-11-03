#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117527537.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char buffer[BUFF_SIZE] = {0}; // buffer for line
    char result[BUFF_SIZE] = {0}; // buffer for final output

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        size_t len = strlen(buffer);

        // Replace trailing newline with null terminator
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }

        int frequencies[BUFF_SIZE] = {0};
        char ch = 0;

        // Count character frequencies
        for (size_t i = 0; i < len; i++) {
            ch = buffer[i];
            frequencies[(int)ch]++;
        }

        // Append characters that appear once and in order
        for (size_t i = 0; i < len; i++) {
            ch = buffer[i];
            if (frequencies[(int)ch] == 1) {
                size_t curr_len = strlen(result); // Check the length of the string result
                result[curr_len] = ch;            // Append unique letter
                result[curr_len + 1] = '\0';      // Keep null terminating string
            }
        }
    }

    fclose(file); // Close file

    printf("%s\n", result);

    return 0;
}
