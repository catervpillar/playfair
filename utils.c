
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"
#include "fileManager.h"

/**
 * Allocates a new string of the given @size (comprehensive of the '\0')
 * and returns a pointer to the first element.
 * If the allocation fails, an error occurs and the program ends.
 *
 * @param size - the length of the string to allocate
 * @return a pointer to the first element of the allocated string
 */
char *stringMalloc(size_t size) {
    char *newString = (char *) malloc(sizeof(char) * size);
    if (newString == NULL) {
        fprintf(stderr, "\nERROR: The memory allocation has failed\n\n");
        exit(EXIT_FAILURE);
    }
    return newString;
}

/**
 * Creates a new string by reallocating the given one using the given size
 * and returns a pointer to its first element.
 *
 * @param in - the string to reallocate
 * @param size - the length of the new string
 * @return a pointer to the first element of the reallocated string
 */
char *stringRealloc(char *in, size_t size) {
    char *reallocatedString = (char *) realloc(in, sizeof(char) * size);
    if (reallocatedString == NULL) {
        fprintf(stderr, "\nERROR: The memory allocation has failed\n\n");
        free(in);
        exit(EXIT_FAILURE);
    }
    return reallocatedString;
}

/**
 * Change every single letter of the given text to uppercase.
 *
 * @param text - the text to capitalize
 */
void toUpperString(char *text) {
    while (*text != '\0') {
        if (isupper(*text) == 0) *text = (char) toupper(*text);
        text++;
    }
}

/**
 * Checks the given text to find possible occurrences of the @MISSING_CHAR
 * (defined previously when creating the KEYFILE) and, if there are any,
 * the @MISSING_CHAR is substituted with the @replacementChar.
 *
 * @param text - the text to check
 * @param replacementCharacter - the replacement character to use
 */
void substituteMissingCharacter(char *text, char replacementCharacter) {
    extern char MISSING_CHAR;
    if (isalpha(MISSING_CHAR) != 0)
        while (*text != '\0') {
            if (*text == MISSING_CHAR) *text = replacementCharacter;
            text++;
        }
}

/**
 * Copies the given text to a new string two letter at a time and, if two equal
 * letters occur, a @specialCharacter is inserted between them.
 *
 * @param text - the text to check
 * @param specialCharacter - the special character to use to separate equal letters
 * @return a pointer to the first element of the new string
 */
char *addSpecialCharactersBetweenDoubles(char *text, char specialCharacter) {
    size_t textSize = strlen(text);
    char *processedText = stringMalloc(textSize + 1);
    int counter = 0;

    while (*text != '\0') {
        processedText[counter++] = *text;
        text++;
        if (*text != '\0') {
            if (processedText[counter - 1] != *text) {
                processedText[counter++] = *text;
                text++;
            } else {
                textSize++;
                processedText = stringRealloc(processedText, textSize + 1);
                processedText[counter++] = specialCharacter;
            }
        }
    }
    processedText[counter] = '\0';
    return processedText;
}

/**
 * The method receives a text whose length is odd and copies its content to
 * a new string and eventually adds one letter at the end to make the length
 * even.
 * The letter which is added at the end of the new string is either a new letter
 * read from the given file (if and only if there are any left and if such letter
 * is not equal to the last of the given text) or the @specialCharacter from the
 * given KEYFILE.
 *
 * @param text - the text that needs to be added a new letter
 * @param keyFile - the KEYFILE whose @specialCharacter needs to be used
 * @param file - the file where to read from possible next letter
 * @return a pointer to the first element of the new string
 */
char *addLastLetter(char *text, KEYFILE keyFile, FILE *file) {
    char *processedText = stringMalloc(strlen(text) + 2);
    int counter = 0;

    while (*text != '\0') {
        processedText[counter++] = *text;
        text++;
    }

    long currentPosition = ftell(file);
    size_t fileSize = getFileSize(file);

    if (currentPosition == fileSize) {
        processedText[counter++] = keyFile.specialCharacter;
    } else {
        char nextLetter = readNextLetterFromFile(file, keyFile.replacementCharacter);
        if (processedText[counter - 1] != nextLetter)
            processedText[counter++] = nextLetter;
        else {
            processedText[counter++] = keyFile.specialCharacter;
            fseek(file, -1, SEEK_CUR);
        }
    }

    processedText[counter] = '\0';
    return processedText;
}