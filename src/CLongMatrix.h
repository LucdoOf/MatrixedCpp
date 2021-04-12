#ifndef MATRIXEDCPP_CLONGMATRIX_H
#define MATRIXEDCPP_CLONGMATRIX_H

#include "CMatrix.h"


class CLongMatrix : public CMatrix<long>{
public:
    void MATPrintItem(long const& item) override;
};


#endif //MATRIXEDCPP_CLONGMATRIX_H
