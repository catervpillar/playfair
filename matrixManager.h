
#include "keyFileManager.h"

#ifndef PLAYFAIR_MATRIXMANAGER_H
#define PLAYFAIR_MATRIXMANAGER_H

typedef struct {
    char **matrix;
} MATRIX;

char **matrixMalloc(size_t dimension);

MATRIX createMatrix(KEYFILE keyfile);

void fillMatrix(MATRIX *matrix, const char *matrixText);

char *getMatrixText(KEYFILE keyFile);

#endif //PLAYFAIR_MATRIXMANAGER_H