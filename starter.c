
#include <stdlib.h>
#include "starter.h"
#include "keyFileManager.h"
#include "matrixManager.h"
#include "printer.h"
#include "fileManager.h"
#include "cipherManager.h"

/**
 * Creates all the necessary structures and starts the encoding/decoding of
 * the given files.
 *
 * @param argc - the command's number of parameters
 * @param argv - the command's list of the parameters
 */
void startPlayfair(int argc, char **argv) {
    KEYFILE keyFile = createKeyFileFromFile(argv[2]);
    MATRIX playfairMatrix = createMatrix(keyFile);
    printStructures(keyFile, playfairMatrix);

    for (int i = 4; i < argc; i++) {
        printf("\ninput %d: %s\n", i - 3, argv[i]);
        char *outputPath = getOutputFilePath(argv[3], argv[i], getExtension(argv[1]));
        processFile(argv[i], outputPath, playfairMatrix, keyFile, argv[1]);
        printf("output %d: %s\n", i - 3, outputPath);
        free(outputPath);
    }
}