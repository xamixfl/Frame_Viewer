#include "getline.h"

#ifdef _MSC_VER

ssize_t getline(char** lineptr, size_t* n, FILE* stream) {
    if (!lineptr || !n || !stream)
        return -1;

    if (!*lineptr || *n == 0) {
        *n = GETLINE_INIT_SIZE;
        *lineptr = (char*)malloc(*n);
        if (!*lineptr)
            return -1;
    }

    size_t pos = 0;
    int c;

    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n * 2;
            char* new_ptr = (char*)realloc(*lineptr, new_size);
            if (!new_ptr)
                return -1;
            *lineptr = new_ptr;
            *n = new_size;
        }

        (*lineptr)[pos++] = (char)c;

        if (c == '\n')
            break;
    }

    if (pos == 0)
        return -1;

    (*lineptr)[pos] = '\0';

    return (ssize_t)pos;
}

#endif
