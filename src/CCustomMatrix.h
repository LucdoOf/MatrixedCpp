#ifndef MATRIXEDCPP_CCUSTOMMATRIX_H
#define MATRIXEDCPP_CCUSTOMMATRIX_H

#include <iostream>
#include "CMatrix.h"

template <typename T>
class CCustomMatrix : public CMatrix<T>{
public:
    void MATPrintItem(T const& item) override {
        std::cout << item << std::endl;
    }
    CCustomMatrix(T** pMATItems, int iMATLines, int iMATColumns);
};

template<typename T>
CCustomMatrix<T>::CCustomMatrix(T** pMATItems, int iMATLines, int iMATColumns) : CMatrix<T>(pMATItems, iMATLines, iMATColumns){

}


#endif //MATRIXEDCPP_CCUSTOMMATRIX_H
