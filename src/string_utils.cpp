#include "string_utils.h"
#include <cstdio>
#include <iostream>

char* strMultiCat(int count, ...) {
    va_list ap;
    va_start(ap, count);
    unsigned long toReturnSize = sizeof(char *);
    char* toReturn = (char*) malloc(toReturnSize);
    for (int i = 0; i < count; i++) {
        char* string = va_arg(ap, char*);
        if (string == nullptr) continue;
        int stringSize = (int) sizeof(string);
        toReturnSize += stringSize + sizeof(char);

        toReturn = strSafeCat(toReturn, string);
    }
    va_end(ap);
    return toReturn;
}

char * strSafeCat(char *s1, const char *s2) {
    if (s2 == nullptr) return s1;

    const size_t a = strlen(s1);
    const size_t b = strlen(s2);
    const size_t size_ab = a + b + 1;

    s1 = (char*) realloc(s1, size_ab);

    memcpy(s1 + a, s2, b + 1);

    return s1;
}


// Iterative function to implement itoa() function in C
char* itoa(int value) {
    int base = 10;
    char* buffer = (char*) malloc(sizeof(char) * 100);

    // consider absolute value of number
    int n = abs(value);

    int i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10)
            buffer[i++] = 65 + (r - 10);
        else
            buffer[i++] = 48 + r;

        n = n / base;
    }

    // if number is 0
    if (i == 0)
        buffer[i++] = '0';

    // If base is 10 and value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10)
        buffer[i++] = '-';

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}

// function to reverse buffer[i..j]
char* reverse(char *buffer, int i, int j) {
    while (i < j)
        swap(&buffer[i++], &buffer[j--]);

    return buffer;
}

// inline function to swap two numbers
inline void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}