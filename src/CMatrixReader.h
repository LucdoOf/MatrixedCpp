//
// Created by lucas on 31/03/2021.
//

#include <stdio.h>
#include <string.h>
#include "defines.h"
#include <ctype.h>
#include <stdlib.h>
#include "CMatrix.h"
#include "string_utils.h"
#include <string>


#ifndef MATRIXEDCPP_CMATRIXREADER_H
#define MATRIXEDCPP_CMATRIXREADER_H

class CMatrixReader {

private:
    const char* pMARFilename;
    FILE* MARGetFile();

public:
    explicit CMatrixReader(const char* filename);
    CMatrixReader(CMatrixReader const &reader);
    ~CMatrixReader();
    CMatrix<double> MARRead();
    inline const char* MARGetFilename();

};

#endif //MATRIXEDCPP_CMATRIXREADER_H
