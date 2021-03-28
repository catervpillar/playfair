
#ifndef PLAYFAIR_KEYFILEMANAGER_H
#define PLAYFAIR_KEYFILEMANAGER_H

#include <stdio.h>

typedef struct {
    char *alphabet;
    char replacementCharacter;
    char specialCharacter;
    char *key;
} KEYFILE;

KEYFILE createKeyFileFromFile(char *keyFilePath);

void readKeyFileAlphabet(FILE *file, KEYFILE *keyFile);

void readKeyFileMissingChar(FILE *file, KEYFILE *keyFile);

void readKeyFileSpecialChar(FILE *file, KEYFILE *keyFile);

void readKeyFileKey(FILE *file, size_t fileSize, KEYFILE *keyFile);

void setMissingChar(KEYFILE keyFile);

#endif //PLAYFAIR_KEYFILEMANAGER_H