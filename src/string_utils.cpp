//
// Created by lucas on 07/04/2021.
//

#include "string_utils.h"

char* strMultiCat(int count, ...) {
    va_list ap;
    va_start(ap, count);
    int toReturnSize = sizeof(char *);
    char* toReturn = (char*) malloc(toReturnSize);
    for (int i = 0; i < count; i++) {
        char* string = va_arg(ap, char*);
        toReturn = (char *) realloc(toReturn, toReturnSize + sizeof(string));
        if (toReturn) {
            strcat(toReturn, string);
        } else {
            return nullptr;
        }
    }
    va_end(ap);
    return toReturn;
}