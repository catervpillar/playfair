
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "keyFileManager.h"
#include "fileManager.h"
#include "utils.h"

char MISSING_CHAR = '?';

/**
 * Creates a new KEYFILE reading the necessary data from a specific file
 * opened with the given path.
 * Eventually it sets the missing char from the KEYFILE's alphabet.
 * If the KEYFILE is empty, an error is printed and the program ends.
 * If the key contains the missing character from the alphabet, it is
 * substituted with the replacement character.
 *
 * @param keyFilePath - the path of the file from which the data has to be read
 * @return the new KEYFILE
 */
KEYFILE createKeyFileFromFile(char *keyFilePath) {
    FILE *file = openFile(keyFilePath, "r+");
    size_t fileSize = getFileSize(file);

    if (fileSize == 0) {
        fprintf(stderr, "ERROR: the KEYFILE is empty!\n\n");
        exit(EXIT_FAILURE);
    }

    KEYFILE keyFile;
    readKeyFileAlphabet(file, &keyFile);
    readKeyFileMissingChar(file, &keyFile);
    readKeyFileSpecialChar(file, &keyFile);
    readKeyFileKey(file, fileSize, &keyFile);

    fclose(file);

    setMissingChar(keyFile);
    substituteMissingCharacter(keyFile.key, keyFile.replacementCharacter);
    return keyFile;
}

/**
 * Reads all the characters until the first '\n' from the given file and stores
 * them in the "alphabet" attribute of the given pointer to the struct KEYFILE.
 * If less than 25 letters are read and/or multiple occurrences of the same letter
 * are read within the 25 letters, an error is printed and the program ends.
 * The alphabet is stored in uppercase.
 *
 * @param file - the file from which the alphabet has to be read
 * @param keyFile - the pointer to the struct KEYFILE
 */
void readKeyFileAlphabet(FILE *file, KEYFILE *keyFile) {
    keyFile->alphabet = calloc(26, sizeof(char));
    char c = 0;
    int pos = 0;

    while (c != '\n' && c != EOF) {
        c = (char) fgetc(file);
        if (isalpha(c) != 0) {
            if (strchr(keyFile->alphabet, c) == NULL) {
                keyFile->alphabet[pos++] = c;
                keyFile->alphabet[pos] = '\0';
            }
        }
    }
    if (pos != 25) {
        free(keyFile->alphabet);
        fprintf(stderr, "ERROR: alphabet has the wrong length (expected 25, has %d)!\n\n", pos);
        exit(EXIT_FAILURE);
    }
    toUpperString(keyFile->alphabet);
}

/**
 * Stores the next letter from the file in the "replacementChar" attribute of the
 * given pointer to the struct KEYFILE. The replacement character is stored in uppercase.
 * If the replacement char is not contained in the KEYFILE alphabet or if there's not any
 * replacement char, an error is printed and the program ends.
 *
 * @param file - the file from which the missing character has to be read
 * @param keyFile - the pointer to the struct KEYFILE
 */
void readKeyFileMissingChar(FILE *file, KEYFILE *keyFile) {
    char replChar;
    do {
        replChar = (char) fgetc(file);
    } while (isalpha(replChar) == 0 && replChar != EOF);

    if (replChar == EOF) {
        fprintf(stderr, "ERROR: there is no replacement char in the given file!\n\n");
        exit(EXIT_FAILURE);
    }
    if (strchr(keyFile->alphabet, toupper(replChar)) == NULL) {
        fprintf(stderr, "ERROR: the given replacement char is not contained in the given alphabet!\n\n");
        exit(EXIT_FAILURE);
    }
    keyFile->replacementCharacter = (char) toupper(replChar);
}

/**
 * Stores the next character from the file in the "specialChar" attribute of the
 * given pointer to the struct KEYFILE. The special character is stored in uppercase.
 * Then an "fgetc()" is called to move the file pointer one position forward to skip
 * the next '\n'.
 *
 * @param file - the file from which the special character has to be read
 * @param keyFile - the pointer to the struct KEYFILE
 */
void readKeyFileSpecialChar(FILE *file, KEYFILE *keyFile) {
    char specialChar;
    do {
        specialChar = (char) fgetc(file);
    } while (isalpha(specialChar) == 0 && specialChar != EOF);

    if (specialChar == EOF) {
        fprintf(stderr, "ERROR: there is no special char in the given file!\n\n");
        exit(EXIT_FAILURE);
    }
    if (strchr(keyFile->alphabet, toupper(specialChar)) == NULL) {
        fprintf(stderr, "ERROR: the given special char is not contained in the given alphabet!\n\n");
        exit(EXIT_FAILURE);
    }
    keyFile->specialCharacter = (char) toupper(specialChar);
    fgetc(file);
}

/**
 * Reads forward till the next letter is found. If a next letter is found, the remaining characters
 * of the file (including that letter) are stored in the "key" attribute of the given pointer to the
 * struct KEYFILE.
 * If there are no letters left, the key is considered to be null.
 * The key is stored in uppercase.
 *
 * @param file - the file from which the data has to be read
 * @param fileSize - the size of the given file
 * @param keyFile - the pointer to the struct KEYFILE
 */
void readKeyFileKey(FILE *file, size_t fileSize, KEYFILE *keyFile) {
    char firstLetter;

    do {
        firstLetter = (char) fgetc(file);
    } while (isalpha(firstLetter) == 0 && firstLetter != EOF);

    if (firstLetter != EOF)
        fseek(file, -1, SEEK_CUR);

    long currPos = ftell(file);
    keyFile->key = stringMalloc(fileSize - currPos + 1);

    fread(keyFile->key, sizeof(char), (fileSize - currPos), file);
    keyFile->key[fileSize - currPos] = '\0';
    toUpperString(keyFile->key);
}

/**
 * Compares the KEYFILE alphabet attribute with the defined char ALPHA (which
 * contains all the letters) to find which characters of the 26 is missing.
 * The missing character is then stored in @MISSING_CHAR.
 *
 * @param keyFile - the KEYFILE whose alphabet is needed to find the missing char
 */
void setMissingChar(KEYFILE keyFile) {
    char ALPHA[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(ALPHA); i++) {
        if (strchr(keyFile.alphabet, ALPHA[i]) == NULL) {
            MISSING_CHAR = ALPHA[i];
            break;
        }
    }
}