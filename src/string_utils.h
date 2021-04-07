//
// Created by lucas on 07/04/2021.
//

#ifndef MATRIXEDCPP_STRING_UTILS_H
#define MATRIXEDCPP_STRING_UTILS_H

#include <stdlib.h>
#include <string.h>
#include<stdarg.h>

char* strMultiCat(int count, ...);

char* itoa(int num);

char* reverse(char *buffer, int i, int j);

inline void swap(char *x, char *y);

char * strSafeCat(char *s1, const char *s2);

#endif //MATRIXEDCPP_STRING_UTILS_H
