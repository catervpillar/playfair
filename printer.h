
#ifndef PLAYFAIR_PRINTER_H
#define PLAYFAIR_PRINTER_H

#include "keyFileManager.h"
#include "matrixManager.h"
#include <stddef.h>

void printStructures(KEYFILE keyfile, MATRIX playfairMatrix);

void printKeyFile(KEYFILE keyFile);

void printMatrix(char **matrix, size_t dimension);

void printWrongNumberOfParameters(int n);

void printUnknownCommand(char *command);

void printCommandLineFlags();

void printCorrectCommand();

void printCommandInfo();

void printHelp();

void printInfo();

void printVersion();

void printTitle();

#endif //PLAYFAIR_PRINTER_H
