
#include <string.h>
#include <stdlib.h>

#include "fileManager.h"
#include "utils.h"
#include "cipherManager.h"

/**
 * Macro for returning the smaller of two numbers.
 */
#define MIN(a, b) (((a) <= (b)) ? (a) : (b))

/**
 * The default amount of characters to read from the file at a time (if possible).
 */
#define BUFFER 500000

/**
 * Opens the input file using the given path, then reads @BUFFER characters at a time (if possible,
 * otherwise the remaining ones) until the end of the file is reached.
 * If the file is empty, an error is printed and the program ends.
 * With the method @getProcessedText() it obtains the processed portion of the file (encoded or decoded,
 * depending on the @command parameter, using the given @KEYFILE and the given @MATRIX).
 * The result of the encoding/decoding is written to the file specified by the given output path.
 * If the first portion of the file is encoded/decoded, it is written to a new file (if a file with the same
 * name already exists, its content is erased and the file is considered as a new empty file).
 * Otherwise, it is appended to an existing file.
 * When there are no more letters to read from the file, the file is closed.
 *
 * @param filePath - the path of the input file to encode or decode
 * @param outputPath - the output path of the file where to write the encoded or decoded text
 * @param playfairMatrix - the MATRIX used to encode/decode
 * @param keyFile - the KEYFILE whose attributes are needed for the preparation of the text to process
 * @param command - the desired operation to execute (whether "encode" or "decode")
 */
void processFile(char *filePath, char *outputPath, MATRIX playfairMatrix, KEYFILE keyFile, char *command) {
    FILE *file = openFile(filePath, "r+");
    size_t fileSize = getFileSize(file);

    if (fileSize == 0) {
        fprintf(stderr, "\nERROR: the file to %s is empty!\n\n", command);
        exit(EXIT_FAILURE);
    }

    size_t remainingCharacter = fileSize;
    size_t nCharToRead;

    while (remainingCharacter > 0) {
        nCharToRead = MIN(BUFFER, remainingCharacter);
        char *processedText = getProcessedText(file, nCharToRead, playfairMatrix, keyFile, command);

        if (remainingCharacter == fileSize)
            writeToNewFile(outputPath, processedText);
        else appendToExistingFile(outputPath, processedText);

        free(processedText);
        remainingCharacter = fileSize - ftell(file);
    }
    fclose(file);
}

/**
 * Reads @nCharToRead from the given file and then fixes the text to prepare it to the encode/decode operation.
 * It checks and corrects any occurrence of the missing char with the method @substituteMissingCharacter().
 * Then the special char from the keyFile is added between doubles and eventually to the end of the text if it
 * has an odd length.
 * Eventually the encoded or decoded text (depending on the @command parameter) is returned.
 *
 * @param file - the input file where to read from
 * @param nCharToRead - the number of chars to read from the given file
 * @param playfairMatrix - the MATRIX used to encode/decode
 * @param keyFile - the KEYFILE whose attributes are needed for the fixing of the text
 * @param command - the desired operation to execute (whether "encode" or "decode")
 * @return the encoded or decoded text
 */
char *getProcessedText(FILE *file, size_t nCharToRead, MATRIX playfairMatrix, KEYFILE keyFile, char *command) {
    char *finalText;
    char *text = readTextFromFile(file, nCharToRead);
    substituteMissingCharacter(text, keyFile.replacementCharacter);

    char *fixedText = addSpecialCharactersBetweenDoubles(text, keyFile.specialCharacter);
    free(text);

    if (strlen(fixedText) % 2 != 0) {
        finalText = addLastLetter(fixedText, keyFile, file);
    } else {
        finalText = stringMalloc(strlen(fixedText) + 1);
        strcpy(finalText, fixedText);
    }
    free(fixedText);
    return encoder(playfairMatrix, finalText, command);
}

/**
 * Encodes or decodes the given text two letters at a time depending on the @command
 * parameter (that is whether "encode" or "decode") using the appropriate Playfair
 * Cipher rules.
 * The two letters' coordinates in the matrix are found and then the correct
 * encoded or decoded letters are obtained using the appropriate methods.
 *
 * @param playfairMatrix - the MATRIX used to encode/decode
 * @param text - the text to encode or decode
 * @param command - the desired operation to execute (whether "encode" or "decode")
 * @return the encoded or decoded text
 */
char *encoder(MATRIX playfairMatrix, char *text, char *command) {
    char *processedText = stringMalloc(strlen(text) + 1);
    CHAR_COORDINATES coordinates1, coordinates2;
    int counter = 0;

    while (*text != '\0') {
        coordinates1 = getCoordinates(*text, playfairMatrix);
        text++;
        coordinates2 = getCoordinates(*text, playfairMatrix);

        if (coordinates1.row == coordinates2.row) {
            processedText[counter++] = sameRowRule(coordinates1, playfairMatrix, command);
            processedText[counter++] = sameRowRule(coordinates2, playfairMatrix, command);
        } else if (coordinates1.column == coordinates2.column) {
            processedText[counter++] = sameColumnRule(coordinates1, playfairMatrix, command);
            processedText[counter++] = sameColumnRule(coordinates2, playfairMatrix, command);
        } else {
            processedText[counter++] = playfairMatrix.matrix[coordinates1.row][coordinates2.column];
            processedText[counter++] = playfairMatrix.matrix[coordinates2.row][coordinates1.column];
        }
        text++;
    }

    processedText[counter] = '\0';
    return processedText;
}

/**
 * This method receives the coordinates of a certain character in the given matrix and
 * returns the one before (same row but previous column) or after it (same row but next column),
 * depending on whether the @command is "encode" or "decode". This method follows the specific
 * rule of the "letters in the same row" as described in the Playfair Cipher encoding/decoding
 * procedure.
 *
 * @param coordinates - the coordinates of the character to encode/decode
 * @param playfairMatrix - the MATRIX where to search the new character to return
 * @param command - the desired operation to execute (whether "encode" or "decode")
 * @return
 */
char sameRowRule(CHAR_COORDINATES coordinates, MATRIX playfairMatrix, char *command) {
    if (strcmp(command, "encode") == 0) {
        if (coordinates.column < 4)
            return playfairMatrix.matrix[coordinates.row][coordinates.column + 1];
        else return playfairMatrix.matrix[coordinates.row][0];
    } else if (strcmp(command, "decode") == 0) {
        if (coordinates.column > 0)
            return playfairMatrix.matrix[coordinates.row][coordinates.column - 1];
        else return playfairMatrix.matrix[coordinates.row][4];
    } else return -1;
}

/**
 * This method receives the coordinates of a certain character in the given matrix and
 * returns the one above (in the previous row and same column) or below (in the next row
 * and same column) it, depending on whether the @command is "encode" or "decode".
 * This method follows the specific rule of the "letters in the same column" as described
 * in the Playfair Cipher encoding/decoding procedure.
 *
 * @param coordinates - the coordinates of the character to encode/decode
 * @param playfairMatrix - the MATRIX where to search the new character to return
 * @param command - the desired operation to execute (whether "encode" or "decode")
 * @return
 */
char sameColumnRule(CHAR_COORDINATES coordinates, MATRIX playfairMatrix, char *command) {
    if (strcmp(command, "encode") == 0) {
        if (coordinates.row < 4)
            return playfairMatrix.matrix[coordinates.row + 1][coordinates.column];
        else return playfairMatrix.matrix[0][coordinates.column];
    } else if (strcmp(command, "decode") == 0) {
        if (coordinates.row > 0)
            return playfairMatrix.matrix[coordinates.row - 1][coordinates.column];
        else return playfairMatrix.matrix[4][coordinates.column];
    } else return -1;
}

/**
 * This method receives a certain character and looks for it in the given matrix.
 * If the character is found, its coordinates are stored in the specific
 * @CHAR_COORDINATES struct which is returned.
 * If the matrix does not contain the given character and so the @row and @column
 * attributes of the struct are equal to "-1", an error is printed and the program
 * ends.
 *
 * @param charToFind - the character to find
 * @param playfairMatrix - the MATRIX where to search the character
 * @return the coordinates of the given character
 */
CHAR_COORDINATES getCoordinates(char charToFind, MATRIX playfairMatrix) {
    CHAR_COORDINATES coordinates;
    coordinates.row = -1;
    coordinates.column = -1;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (playfairMatrix.matrix[i][j] == charToFind) {
                coordinates.row = i;
                coordinates.column = j;
            }
    if (coordinates.row == -1 | coordinates.column == -1) {
        fprintf(stderr, "\nERROR: the matrix does not contain the specified character '%c'", charToFind);
        exit(EXIT_FAILURE);
    }
    return coordinates;
}