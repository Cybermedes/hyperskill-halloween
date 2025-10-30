#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *toBinaryString(long long int number);

int main(void) {
    FILE *file = fopen("hyperskill-dataset-117460134.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return EXIT_FAILURE;
    }

    char number[64] = {0};
    fgets(number, sizeof(number), file);
    fclose(file);
    number[sizeof(number) - 1] = '\0';

	// Remove newline character
    for (size_t i = 0; i < sizeof(number) / sizeof(number[0]); i++) {
        if (number[i] == '\n') {
            number[i] = '\0';
            break;
        }
    }

    long long int phoneNumber = strtoll(number, NULL, 10);
    long long int uintMax = UINT32_MAX + 1LL; // Exercise considers 2^32 not 2^32-1.
    int numberOfOverflows = 0;

    while (phoneNumber >= uintMax) {
        phoneNumber -= uintMax;
        numberOfOverflows++;
    }

    // Format example: 1,11001010001001111000111011001100
    char *binaryPhoneNumber = toBinaryString(phoneNumber);
    printf("%d,%s\n", numberOfOverflows, binaryPhoneNumber);
    free(binaryPhoneNumber);

    return 0;
}

/*
 * Convert an integer to a binary string
 */
char *toBinaryString(long long int number) {
    // Handle special case for 0 (zero)
    if (number == 0) {
        char *result = malloc(2);
        if (result == NULL) {
            perror("Failed to allocate memory");
            return NULL;
        }

        strcpy(result, "0");
        return result;
    }

    // Calculate number of bits needed
    long long int temp = number;
    int bitCount = 0;
    while (temp != 0) {
        bitCount++;
        temp >>= 1;
    }

    // Allocate memory for binary string (+1 for null terminator)
    char *binary = malloc(bitCount + 1);
    if (binary == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Convert to binary
    int index = bitCount - 1;
    temp = number;

    while (temp != 0) {
        binary[index] = (temp & 1) ? '1' : '0';
        temp >>= 1;
        index--;
    }

    binary[bitCount] = '\0'; // Null terminate the string
    return binary; // Return pointer to memory allocated string
}
