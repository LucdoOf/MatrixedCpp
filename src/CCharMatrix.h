#ifndef MATRIXEDCPP_CCHARMATRIX_H
#define MATRIXEDCPP_CCHARMATRIX_H

#include "CMatrix.h"


class CCharMatrix : public CMatrix<char>{
public:
    void MATPrintItem(char const& item) override;
};


#endif //MATRIXEDCPP_CCHARMATRIX_H
