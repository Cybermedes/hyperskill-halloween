#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117584701.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    size_t buffer_size = 1024;
    char *buffer = calloc(buffer_size, sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    char ch = 0;
    size_t len = 0;
    while ((ch = fgetc(file)) != EOF && ch != '\n' && ch != '\r') {

        if (len + 1 >= buffer_size) {
            buffer_size *= 2;
            char *temp = realloc(buffer, buffer_size);
            if (temp == NULL) {
                perror("Failed to reallocate memory");
                free(buffer);
                fclose(file);
                return EXIT_FAILURE;
            }
            buffer = temp;
        }

        buffer[len++] = (char)ch;
    }
    buffer[len] = '\0';

    fclose(file); // Close file

    // Use Sliding Window algorithm

    int count[26] = {0}; // how many times each letter appears in the current window
    int unique = 0;      // how many unique letters from A to G are inside the window
    size_t left = 0, right = 0, best_len = len + 1, best_start = 0;
    int idx = 0, li = 0;

    while (right < len) {
		// Expand window to the left until it contains all 7 letters
        idx = buffer[right] - 'A';
        if (count[idx] == 0 && buffer[right] >= 'A' && buffer[right] <= 'G') {
            unique++;
        }
        count[idx]++;
        right++;

        // it means our current window contains all 7 letters and process current string
        while (unique == 7) {
            // Check if this window is the shortest so far
            if (right - left < best_len) {
                best_len = right - left;
                best_start = left;
            }

            // Remove one letter from the left, if one of the 7 letters is removed, the
            // loop exit and then right start increasing again
            li = buffer[left] - 'A';
            count[li]--;
            if (buffer[left] >= 'A' && buffer[left] <= 'G' && count[li] == 0)
                unique--;
            left++;
        }
    }

    if (best_len <= len)
        printf("Result: %.*s\n", (int)best_len, buffer + best_start);

    free(buffer); // Free memory

    return 0;
}
