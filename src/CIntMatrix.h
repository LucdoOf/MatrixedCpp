#ifndef MATRIXEDCPP_CINTMATRIX_H
#define MATRIXEDCPP_CINTMATRIX_H

#include "CMatrix.h"


class CIntMatrix : public CMatrix<int>{
public:
    void MATPrintItem(int const& item) override;
    CIntMatrix(int** pMATItems, int iMATLines, int iMATColumns);
};


#endif //MATRIXEDCPP_CINTMATRIX_H
