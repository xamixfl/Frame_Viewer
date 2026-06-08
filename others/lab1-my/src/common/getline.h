#ifndef GETLINE_H
#define GETLINE_H

#ifdef _MSC_VER

#include <stdio.h>
#include <stdlib.h>
#include <BaseTsd.h>

typedef SSIZE_T ssize_t;

#define GETLINE_INIT_SIZE 128

ssize_t getline(char** lineptr, size_t* n, FILE* stream);

#endif

#endif // GETLINE_H