#ifndef MATRIXEDCPP_CFLOATMATRIX_H
#define MATRIXEDCPP_CFLOATMATRIX_H

#include "CMatrix.h"


class CFloatMatrix : public CMatrix<float>{
public:
    void MATPrintItem(float const& item) override;
};


#endif //MATRIXEDCPP_CFLOATMATRIX_H
