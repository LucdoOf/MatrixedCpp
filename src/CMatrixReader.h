//
// Created by lucas on 31/03/2021.
//

#include <stdio.h>
#include <string.h>
#include "defines.h"
#include <ctype.h>

#ifndef MATRIXEDCPP_CMATRIXREADER_H
#define MATRIXEDCPP_CMATRIXREADER_H


class CMatrixReader {

private:
    char* pMARFilename;
    FILE* MARGetFile();

public:
    CMatrixReader(char* filename);
    CMatrixReader(const CMatrixReader reader);
    ~CMatrixReader();
    MARRead();
    inline MARGetFilename();

};


#endif //MATRIXEDCPP_CMATRIXREADER_H
