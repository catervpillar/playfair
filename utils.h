
#include <stddef.h>
#include <stdio.h>
#include "keyFileManager.h"

#ifndef PLAYFAIR_UTIL_H
#define PLAYFAIR_UTIL_H

char *stringMalloc(size_t size);

char *stringRealloc(char *in, size_t size);

void toUpperString(char *text);

void substituteMissingCharacter(char *text, char replacementCharacter);

char *addSpecialCharactersBetweenDoubles(char *text, char specialCharacter);

char *addLastLetter(char *text, KEYFILE keyFile, FILE *file);

#endif //PLAYFAIR_UTIL_H
