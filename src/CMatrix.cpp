#include "CMatrix.h"
#include <iostream>


template<typename T>
CMatrix<T>::CMatrix(T** pMATItems, int iMATLines, int iMATColumns){
    this->pMATItems = pMATItems;
    this->iMATLines = iMATLines;
    this->iMATColumns = iMATColumns;
}

template<typename T>
CMatrix<T>::CMatrix(const CMatrix<T> &matrix){
    this->pMATItems = matrix.pMATItems;
    this->iMATColumns = matrix.iMATColumns;
    this->iMATLines = matrix.iMATLines;
};

template<typename T>
CMatrix<T>::~CMatrix(){

};

template<typename T>
CMatrix<T> CMatrix<T>::MATTranspose(CMatrix<T> matrix){
    CMatrix<T> toReturn = new CMatrix<T>(&this);
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn.MATSetItemAt(i, j, MATGetItemAt(j, i));
        }
    }
};

template<typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T> &matrix){
    if(matrix.iMATLines == this->MATGetLines() && matrix.iMATColumns == this->MATGetLines()) {
        CMatrix<T> toReturn = new CMatrix<T>(&this);
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < this->iMATColumns; j++) {//HERE
                toReturn.MATSetItemAt(i , j, (this->MATGetItemAt(i, j)) - (matrix->MATGetItemsAt(i, j)));
            }
        }
    } //else throw CMatrixExeception(//TODO);
};

template<typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T> &matrix){
    if(matrix.iMATLines == this->MATGetLines() && matrix.iMATColumns == this->MATGetLines()) {
        CMatrix<T> toReturn = new CMatrix<T>(&this);
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < this->iMATColumns; j++) {//HERE
                toReturn.MATSetItemAt(i , j, (this->MATGetItemAt(i, j)) + (matrix->MATGetItemsAt(i, j)));
            }
        }
    } //else throw CMatrixExeception(//TODO);
};

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T> &matrix){
    if(matrix.iMATColumns == this->MATGetLines() && matrix.iMATLines == this->MATGetLines()) {
        CMatrix<T> toReturn = new CMatrix<T>(&this);
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < this->iMATColumns; j++) {
                for(int k = 0; k < this->MATGetColumns(); ++k) {
                    toReturn.MATSetItemAt(i , j, toReturn.MATGetItemAt(i, j) + (this->MATGetItemAt(i, k)) * (matrix->MATGetItemsAt(k, j)));
                    //mult[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
};

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const float multiplier){
    CMatrix<T> toReturn = new CMatrix<T>(&this);
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn.MATSetItemAt(i, j, MATGetItemAt(i, j) * multiplier);
        }
    }
};

template<typename T>
CMatrix<T> CMatrix<T>::operator*(const int multiplier){
    CMatrix<T> toReturn = new CMatrix<T>(&this);
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn.MATSetItemAt(i, j, MATGetItemAt(i, j) * multiplier);
        }
    }
};

template<typename T> //HERE
CMatrix<T> CMatrix<T>::operator*(const double multiplier){
    CMatrix<T> toReturn = new CMatrix<T>(&this);
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn.MATSetItemAt(i, j, MATGetItemAt(i, j) * multiplier);
        }
    }
};

template<typename T>
inline T CMatrix<T>::MATGetItemAt(int line, int column){
    //HERE
    return *( *(this->pMATItems + line) + column);
};

template<typename T>
inline void CMatrix<T>::MATSetItemAt(int line, int column, T item){
    //HERE
    return *( *(this->pMATItems + line) + column);
};

template<typename T>
inline int CMatrix<T>::MATGetLines(){
    return this->iMATLines;
};

template<typename T>
inline int CMatrix<T>::MATGetColumns(){
    return this->iMATColumns;
};

template<typename T>
void CMatrix<T>::MATPrint(){
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            std::cout << this->MATGetItemAt(i, j) << std::endl;
        }
    }
};
