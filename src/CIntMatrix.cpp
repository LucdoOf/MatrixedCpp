#include "CIntMatrix.h"

void CIntMatrix::MATPrintItem(const int &item) {
    printf("%d ", item);
}

CIntMatrix::CIntMatrix(int** pMATItems, int iMATLines, int iMATColumns) : CMatrix<int>(pMATItems, iMATLines, iMATColumns){

}
