#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 64
#define NUM_VECTORS 1024
#define VEC_SIZE 4

typedef struct Vector {
    int x;
    int y;
    int z;
    int k;
} Vector;

void convert_str_to_vector(const char *data, Vector *vector);

int calculate_euclidean(Vector *vec_a, Vector *vec_b);

int main(void) {

    FILE *file = fopen("hyperskill-dataset-117426476.txt", "r");
    if (file == NULL) {
        perror("Error trying to open file");
        return EXIT_FAILURE;
    }

    Vector *vectors = calloc(NUM_VECTORS, sizeof(Vector));
    if (vectors == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return EXIT_FAILURE;
    }

    int result = 0;
    int counter = 0;
    char buffer[BUFF_SIZE] = {0};

    while (fgets(buffer, sizeof(buffer), file) != NULL && counter < NUM_VECTORS) {
        convert_str_to_vector(buffer, &vectors[counter]);
        counter++;
    }
    fclose(file);

    for (int i = 0; i < counter - 1; i++) {
        result += calculate_euclidean(&vectors[i], &vectors[i + 1]);
    }

    free(vectors);
    printf("Result: %d\n", result);

    return 0;
}

void convert_str_to_vector(const char *data, Vector *vector) {
    char copy[BUFF_SIZE] = {0};
    strncpy(copy, data, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';

    int coord[VEC_SIZE] = {0};
    
    char *token = strtok(copy, ",");
    short i = 0;
    while (token != NULL && i < VEC_SIZE) {
        coord[i] = (int)strtol(token, NULL, 10);
        token = strtok(NULL, ",");
        ++i;
    }

    vector->x = coord[0];
    vector->y = coord[1];
    vector->z = coord[2];
    vector->k = coord[3];
}

int calculate_euclidean(Vector *vec_a, Vector *vec_b) {
    double euclidean = 0.0;

    euclidean = sqrt(pow(vec_a->x - vec_b->x, 2) + pow(vec_a->y - vec_b->y, 2) +
                     pow(vec_a->z - vec_b->z, 2) + pow(vec_a->k - vec_b->k, 2));

    return (int)ceil(euclidean);
}
