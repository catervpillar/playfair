cmake_minimum_required(VERSION 3.17)
project(playfair C)

set(CMAKE_C_STANDARD 99)

add_executable(playfair main.c fileManager.c fileManager.h utils.c utils.h keyFileManager.c keyFileManager.h matrixManager.c matrixManager.h cipherManager.c cipherManager.h printer.c printer.h starter.c starter.h)