
#include <stdio.h>

#ifndef PLAYFAIR_FILEMANAGER_H
#define PLAYFAIR_FILEMANAGER_H

FILE *openFile(char *path, char *mode);

char *readTextFromFile(FILE *file, size_t nChar);

char readNextLetterFromFile(FILE *file, char missingChar);

void writeToNewFile(char *filePath, char *text);

void appendToExistingFile(char *filePath, char *text);

void writeText(FILE *out, char *text);

char *getFileNameFromPath(char *filePath);

char *check_if_string_ends_with(char *str, char *suffix);

char *getOutputFilePath(char *outputDir, char *inputFilePath, char *extension);

char *getExtension(char *command);

char getSeparator();

size_t getFileSize(FILE *file);

#endif //PLAYFAIR_FILEMANAGER_H