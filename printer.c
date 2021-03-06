
#include <stdio.h>
#include <stdlib.h>
#include "printer.h"

/**
 * Prints the two structures of the program: the MATRIX and the KEYFILE.
 * @param keyfile - the keyFile whose attributes need to be printed
 * @param playfairMatrix - the matrix to print
 */
void printStructures(KEYFILE keyfile, MATRIX playfairMatrix) {
    printKeyFile(keyfile);
    printMatrix(playfairMatrix.matrix, 5);
}

/**
 * Prints all the attributes (@alphabet, @replacementCharacter, @specialCharacter
 * and @key) of the given KEYFILE separated by the opportune "\t".
 *
 * @param keyFile - the keyFile whose attributes need to be printed
 */
void printKeyFile(KEYFILE keyFile) {
    printf("\nAlphabet:\t\t%s", keyFile.alphabet);
    printf("\nReplacement char:\t%c", keyFile.replacementCharacter);
    printf("\nSpecial char:\t\t%c", keyFile.specialCharacter);
    printf("\nKey:\t\t\t%s\n", keyFile.key);
}

/**
 * Prints the given matrix with the correct indentation.
 *
 * @param matrix - the matrix to print
 * @param dimension - the dimension of the matrix to print
 */
void printMatrix(char **matrix, size_t dimension) {
    printf("\nMatrix: \n");
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Prints an error for when a wrong amount of parameters are typed.
 */
void printWrongNumberOfParameters(int n) {
    fprintf(stderr, "\nERROR: wrong number of parameters (expected 2 or 5+, are %d)!\n\n", n);
    printCorrectCommand();
    printf("Alternatively, try running with flag '--help' to find out more on how\nto use this program.\n\n");
    exit(EXIT_FAILURE);
}

/**
 * Prints an error for when an unknown command is read.
 */
void printUnknownCommand(char *command) {
    fprintf(stderr, "\nERROR: unknown command '%s'!\n", command);
    printCorrectCommand();
    printf("Alternatively, try running with flag '--help' to find out more on how\nto use this program.\n\n");
    exit(EXIT_FAILURE);
}

/**
 * Prints a list of all the command line flags for this program.
 */
void printCommandLineFlags() {
    printf("LIST OF COMMAND LINE FLAGS:\n");
    printf("'--help' or '-h'\t"
           "Prints the info of the program.\n\n");
    printf("'--version' or '-v'\t"
           "Prints the current version of the program.\n\n");
}

/**
 * Prints the program's info showing the correct syntax to write
 * the encode or decode command.
 */
void printCorrectCommand() {
    printf("\nCORRECT SYNTAX FOR ENCODING-DECODING:\n");
    printf("'<playfair> <encode|decode> <keyfile> <outputdir> <file1> ... <filen>'\n");
    printf("\nALTERNATIVE SYNTAX:\n");
    printf("'<playfair> <flag>'\n\n");
}

/**
 * Prints an explanation of the various arguments of the correct syntax of the command.
 */
void printCommandInfo() {
    printf("SYNTAX EXPLANATION:\n");
    printf("<playfair>\t\tThe name of the compiled file.\n\n");
    printf("<flag>\t\t\tThe command line flag to run with.\n\n");
    printf("<encode|decode>\t\tDescribes which action to\n\t\t\tperform ('encode' for encoding,\n\t\t\t'decode' for decoding).\n\n");
    printf("<keyfile>\t\tThe path of the file containing\n\t\t\tall the KeyFile attributes.\n\n");
    printf("<outputdir>\t\tThe output directory where the\n\t\t\tencoded and decoded files\n\t\t\twill be saved.\n\n");
    printf("<file1> ... <filen>\tAll the paths of each file\n\t\t\tto encode/decode.\n\n");
}

/**
 * Prints the program's info (generated by commands '-h' or '--help') and terminates
 * the program.
 */
void printHelp() {
    printInfo();
    printCorrectCommand();
    printCommandInfo();
    printCommandLineFlags();
    exit(EXIT_SUCCESS);
}

void printInfo() {
    printf("This code has been written for the attainment of the laboratory part\n"
           "of the 'Operating Systems' exam at the Bacheleror Degree in Computer\n"
           "Science at University of Camerino.\n"
           "It consists of an implementation of the famous Playfair Cipher, a\n"
           "manual symmetric encryption technique invented in 1854 by Charles\n"
           "Wheatstone bearing the name of Lord Playfair for promoting its use.\n\n"
           "This application allows the user to encode and decode multiple files\n"
           "using a certain KEYFILE, producing correspondent '.pf' files as a\n"
           "result of the encoding and '.dec' files as a result of the decoding.\n\n"
           "To execute the program, please type a command as shown below:\n");
}

/**
 * Prints the current version of the program
 */
void printVersion() {
    printf("playfair cipher version 2.0.0 (14-2-2021)(credits: Tommaso Catervi)\n\n");
    exit(EXIT_SUCCESS);
}

/**
 * Prints the title of the program as an ASCII art text.
 */
void printTitle() {
    printf("\n");
    printf(" _____  _              __      _         _____ _       _               \n");
    printf("|  __ \\| |            / _|    (_)       / ____(_)     | |              \n");
    printf("| |__) | | __ _ _   _| |_ __ _ _ _ __  | |     _ _ __ | |__   ___ _ __ \n");
    printf("|  ___/| |/ _` | | | |  _/ _` | | '__| | |    | | '_ \\| '_ \\ / _ \\ '__|\n");
    printf("| |    | | (_| | |_| | || (_| | | |    | |____| | |_) | | | |  __/ | \n");
    printf("|_|    |_|\\__,_|\\__, |_| \\__,_|_|_|     \\_____|_| .__/|_| |_|\\___|_|  \n");
    printf("                 __/ |                          | |                    \n");
    printf("                |___/                           |_| \n\n");
}