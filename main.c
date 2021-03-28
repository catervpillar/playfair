
#include "printer.h"
#include "utils.h"
#include "matrixManager.h"
#include "fileManager.h"
#include "starter.h"

#include <stdlib.h>
#include <string.h>


/**
 * Returns the appropriate command word for cleaning the console
 * depending on the current OS.
 *
 * @return "cls" if Windows, "clear" otherwise
 */
const char *getConsoleClearCommand() {
#ifdef _WIN32
    return "cls";
#else
    return "clear";
#endif
}

int main(int argc, char **argv) {
    system(getConsoleClearCommand());
    printTitle();

    switch (argc) {
        case 1:
        case 3:
        case 4:
            printWrongNumberOfParameters(argc);
        case 2:
            if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)
                printHelp();
            else if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)
                printVersion();
            else printUnknownCommand(argv[1]);
        default:
            if (strcmp(argv[1], "encode") != 0 && strcmp(argv[1], "decode") != 0)
                printUnknownCommand(argv[1]);
            else
                startPlayfair(argc, argv);
            break;
    }
    return 0;
}