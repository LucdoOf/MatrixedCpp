#ifndef MATRIXEDCPP_CDOUBLEMATRIX_H
#define MATRIXEDCPP_CDOUBLEMATRIX_H

#include "CMatrix.h"


class CDoubleMatrix : public CMatrix<double> {
public:
    void MATPrintItem(double const& item) override;
};


#endif //MATRIXEDCPP_CDOUBLEMATRIX_H
