
#ifndef PLAYFAIR_CIPHERMANAGER_H
#define PLAYFAIR_CIPHERMANAGER_H

#include "keyFileManager.h"
#include "matrixManager.h"

typedef struct {
    int row;
    int column;
} CHAR_COORDINATES;

void processFile(char *filePath, char *outputPath, MATRIX playfairMatrix, KEYFILE keyFile, char *command);

char *getProcessedText(FILE *file, size_t nCharToRead, MATRIX playfairMatrix, KEYFILE keyFile, char *command);

char *encoder(MATRIX playfairMatrix, char *text, char *command);

char sameRowRule(CHAR_COORDINATES coordinates, MATRIX playfairMatrix, char *command);

char sameColumnRule(CHAR_COORDINATES coordinates, MATRIX playfairMatrix, char *command);

CHAR_COORDINATES getCoordinates(char charToFind, MATRIX playfairMatrix);

#endif //PLAYFAIR_CIPHERMANAGER_H