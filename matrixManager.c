
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "utils.h"
#include "matrixManager.h"

/**
 * Allocates a new matrix and returns it.
 * If the allocation fails, an error occurs and the program ends.
 *
 * @param dimension - the dimension of the matrix to create
 * @return the new matrix allocated
 */
char **matrixMalloc(size_t dimension) {
    char **matrix = (char **) malloc(dimension * sizeof(char *));
    if (matrix == NULL) {
        fprintf(stderr, "\nERROR: The matrix memory allocation has failed\n\n");
        exit(EXIT_FAILURE);
    }
    for (int row = 0; row < dimension; row++) {
        matrix[row] = stringMalloc(dimension);
    }
    return matrix;
}

/**
 * Creates a new MATRIX struct and fills its @matrix attribute with a text generated with the
 * apposite method by using the given keyFile.
 *
 * @param keyfile - the keyFile to use to generate the matrix text
 * @return the new MATRIX struct
 */
MATRIX createMatrix(KEYFILE keyfile) {
    MATRIX matrix;
    fillMatrix(&matrix, getMatrixText(keyfile));
    return matrix;
}

/**
 * Fills the given matrix with the given text.
 *
 * @param matrix - the matrix to fill
 * @param matrixText - the text to use to fill the matrix
 */
void fillMatrix(MATRIX *matrix, const char *matrixText) {
    matrix->matrix = matrixMalloc(5);
    int pos = 0;

    for (int row = 0; row < 5; row++) {
        for (int column = 0; column < 5; column++) {
            matrix->matrix[row][column] = matrixText[pos];
            pos++;
        }
    }
}

/**
 * Creates a new char* (whose size is the same number as the matrix cells) which is the text
 * that will be used to fill the matrix.
 * It is created by inserting all the char of the @key attribute of the keyFile without repeating
 * the same letters and then adding the remaining letters of the @alphabet of the keyFile that
 * haven't been inserted yet.
 *
 * @param keyFile - the keyFile whose attributes are required for the composition of the text
 * @param matrixDim - the dimension (nRows = nColumns) of the matrix to fill
 * @return the text to fill the matrix
 */
char *getMatrixText(KEYFILE keyFile) {
    char *matrixtext = calloc(26, sizeof(char));
    int pos = 0;

    while (*keyFile.key != '\0') {
        if (isalpha(*keyFile.key) != 0)
            if (strchr(matrixtext, *keyFile.key) == NULL)
                matrixtext[pos++] = *keyFile.key;
        keyFile.key++;
    }
    while (*keyFile.alphabet != '\0') {
        if (strchr(matrixtext, *keyFile.alphabet) == NULL)
            matrixtext[pos++] = *keyFile.alphabet;
        keyFile.alphabet++;
    }
    matrixtext[pos] = '\0';
    return matrixtext;
}

