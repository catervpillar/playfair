
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "fileManager.h"
#include "utils.h"

/**
 * Opens a new file in the specified mode using the specified path
 * and returns a pointer to it.
 * If the operation fails, an error is printed and the program ends.
 *
 * @param path - the path of the file to open
 * @param mode - the mode in which the file has to be opened
 * @return a pointer to the opened file
 */
FILE *openFile(char *path, char *mode) {
    FILE *file = fopen(path, mode);
    if (file == NULL) {
        fprintf(stderr, "\nERROR: the specified file:\n\n'%s'\n\ndoes not exist!\n\n", path);
        exit(EXIT_FAILURE);
    }
    return file;
}

/**
 * Reads text from the specified file one character at a time (for a total of @nchar characters)
 * excluding non-letters. Then the text is changed to uppercase.
 * If no valid text was read, an error is printed and the program ends.
 *
 * @param file - the file to read from
 * @param nChar - the amount of characters
 * @return a pointer to the start of the text
 */
char *readTextFromFile(FILE *file, size_t nChar) {
    char *temp = stringMalloc(nChar + 1);
    int counter = 0;

    for (int i = 0; i < nChar; i++) {
        char c = (char) fgetc(file);
        if (isalpha(c) != 0) temp[counter++] = c;
    }

    if (counter == 0) {
        fprintf(stderr, "\nERROR: no valid text can be read from the specified file");
        exit(EXIT_FAILURE);
    }

    if (counter < nChar)
        temp = stringRealloc(temp, counter + 1);
    temp[counter] = '\0';
    toUpperString(temp);
    return temp;
}

/**
 * Reads forward in the specified file one character at a time until a letter is found
 * or EOF is reached and the the last character that was read is returned (in uppercase).
 * If the last character that was read is the MISSING_CHAR from the KEYFILE alphabet,
 * the substitute character from the KEYFILE is returned instead.
 *
 * @param file - the file to read from
 * @param missingChar - the letter to return in case of bad read
 * @return the last character that was read (in uppercase)
 */
char readNextLetterFromFile(FILE *file, char missingChar) {
    char nextChar;
    extern char MISSING_CHAR;
    do {
        nextChar = (char) fgetc(file);
    } while ((isalpha(nextChar) == 0) && nextChar != EOF);
    if ((char) toupper(nextChar) == MISSING_CHAR)
        return missingChar;
    else return (char) toupper(nextChar);
}

/**
 * Opens a new file in write mode using the specified path and then proceeds to
 * write the whole specified text two letter at a time (separated by a space).
 * If a file with the same name already exists, its content is erased and the file
 * is considered as a new empty file.
 *
 * @param filePath - the file to write to
 * @param text - the text to write to the file
 */
void writeToNewFile(char *filePath, char *text) {
    FILE *file = openFile(filePath, "w");
    writeText(file, text);
    fclose(file);
}

/**
 * Opens a new file in append+ mode using the specified path and then proceeds to
 * append the whole specified text two letter at a time (separated by a space).
 *
 * @param filePath - the file to write to
 * @param text - the text to write to the file
 */
void appendToExistingFile(char *filePath, char *text) {
    FILE *file = openFile(filePath, "a+");
    writeText(file, text);
    fclose(file);
}

/**
 * Writes the given text into the given file two letter at a time
 * (separated by a space).
 *
 * @param out - the file to write into
 * @param text - the text to write into the file
 */
void writeText(FILE *out, char *text) {
    while (*text != '\0') {
        fputc(*text, out);
        text++;
        fputc(*text, out);
        text++;
        if (*text != '\0')
            fputc(' ', out);
    }
}

/**
 * Extracts the name of the file from the given path by searching for the last occurrence of
 * the specific separator used by the current OS (if there are any).
 * Then, if the path ends with ".pf", ".pf" is removed with the apposite method.
 *
 * @param filePath - the path from which the filename is extracted
 * @return the name of the file
 */
char *getFileNameFromPath(char *filePath) {
    char *temp = strrchr(filePath, getSeparator());

    if (temp != NULL)
        return check_if_string_ends_with(temp, ".pf");
    else return check_if_string_ends_with(filePath, ".pf");
}

/**
 * Checks if the given @str ends with the given @suffix and, if it does, it returns a string
 * containing all @str's content but the @suffix.
 * Otherwise, @str is returned.
 *
 * @param str - the string to check
 * @param suffix - the suffix to look for
 * @return the fixed string
 */
char *check_if_string_ends_with(char *str, char *suffix) {
    size_t str_len = strlen(str);
    size_t suffix_len = strlen(suffix);

    if ((str_len >= suffix_len) && (0 == strcmp(str + (str_len - suffix_len), suffix))) {
        char *temp = calloc((str_len - suffix_len), sizeof(char));
        strncpy(temp, str, str_len - suffix_len);
        return temp;
    } else return str;
}

/**
 * Returns the path of the output file of the encode/decode process, which is obtained
 * by combining the output directory path, the name of the input file (obtained through
 * the previous method) and the extension (".pf" for encode, ".dec" for decode).
 *
 * @param outputDir - the path of the output directory
 * @param inputFilePath - the path of the input file
 * @param extension - the extension of the output file
 * @return the path of the output file
 */
char *getOutputFilePath(char *outputDir, char *inputFilePath, char *extension) {
    char *fileName = getFileNameFromPath(inputFilePath);
    size_t size = strlen(outputDir) + strlen(fileName) + strlen(extension);

    char *outputFilePath = stringMalloc(size);

    strcpy(outputFilePath, outputDir);
    strcat(outputFilePath, fileName);
    strcat(outputFilePath, extension);
    //outputFilePath[size] = '\0';

    return outputFilePath;
}

/**
 * Returns the opportune extension depending on the given command:
 * ".pf" for "encode", ".dec" for "decode".
 *
 * @param command - the command defining the type of the operation (encode/decode)
 * @return the opportune extension
 */
char *getExtension(char *command) {
    if (strcmp(command, "encode") == 0)
        return ".pf";
    else
        return ".dec";
}

/**
 * Returns the opportune path separator depending on the current OS.
 * The OS is checked with an #ifdef preprocessor directive (before compilation).
 *
 * @return the opportune separator
 */
char getSeparator() {
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}

/**
 * Calculates the size of the given file by moving the file pointer associated with
 * the given file to the end of it with function "fseek()".
 * Then the file pointer is reset to the same offset as it was at the beginning.
 *
 * @param file - the file whose size needs to be calculated
 * @return the size of the given file
 */
size_t getFileSize(FILE *file) {
    size_t size;
    long currentPosition = ftell(file);
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    fseek(file, currentPosition, SEEK_SET);
    return size;
}