#ifndef MATRIXEDCPP_CSTRINGMATRIX_H
#define MATRIXEDCPP_CSTRINGMATRIX_H

#include "CMatrix.h"


class CStringMatrix : public CMatrix<char*> {
public:
    void MATPrintItem(char* const& item) override;
};


#endif //MATRIXEDCPP_CSTRINGMATRIX_H
