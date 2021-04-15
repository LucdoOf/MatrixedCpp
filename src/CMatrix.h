#ifndef MATRIXEDCPP_CMATRIX_H
#define MATRIXEDCPP_CMATRIX_H

#include <malloc.h>
#include <stdio.h>
#include <iostream>
#include "CMatrixException.h"

template<typename T>
class CMatrix {

public:
    CMatrix(T** pMATItems, int iMATLines, int iMATColumns);
    CMatrix(const CMatrix<T> &matrix);
    CMatrix(int iMATLines, int iMATColumns);
    ~CMatrix();
    CMatrix<T> MATTranspose();
    CMatrix<T> operator-(CMatrix<T> matrix);
    CMatrix<T> operator+(CMatrix<T> matrix);
    CMatrix<T> operator*(CMatrix<T> matrix);
    CMatrix<T> operator*(double multiplier);
    CMatrix<T> operator/(double multiplier);
    T MATGetItemAt(int line, int column);
    void MATSetItemAt(int line, int column, T item);
    int MATGetLines();
    int MATGetColumns();
    void MATPrint();

protected:
    int iMATLines;
    int iMATColumns;
    T** pMATItems;

};

//Constructeur de base
template<typename T>
CMatrix<T>::CMatrix(T** pMATItems, int iMATLines, int iMATColumns){
    this->pMATItems = pMATItems;
    this->iMATLines = iMATLines;
    this->iMATColumns = iMATColumns;
}

//Constructeur de recopie
template<typename T>
CMatrix<T>::CMatrix(const CMatrix<T> &matrix){
    this->pMATItems = matrix.pMATItems;
    this->iMATColumns = matrix.iMATColumns;
    this->iMATLines = matrix.iMATLines;
}

//Constructeur qui initialise à 0
template<typename T>
CMatrix<T>::CMatrix(int iMATLines, int iMATColumns) {
    this->iMATLines = iMATLines;
    this->iMATColumns = iMATColumns;
    this->pMATItems = (T**) malloc(sizeof(T*)*iMATLines);
    for(int h = 0; h < iMATLines; h++){
        this->pMATItems[h] = (T *) malloc(sizeof(T*) * iMATColumns);
    }
    for(int i = 0; i < iMATLines; i++){
        for(int j = 0; j < iMATColumns; j++){
            this->MATSetItemAt(i , j, 0);
        }
    }
}

//Destructeur
template<typename T>
CMatrix<T>::~CMatrix(){
    for(int i = 0; i < iMATLines; i++){
        free(this->pMATItems[i]);
    }
    free(this->pMATItems);
}

//Matrice transposée
template<typename T>
CMatrix<T> CMatrix<T>::MATTranspose(){
    CMatrix<T> toReturn = new CMatrix<T>(this->MATGetLines(), this->MATGetColumns());
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn.MATSetItemAt(i, j, this->MATGetItemAt(j, i));
        }
    }
    return &toReturn;
}

//Surcharge soustraction
template<typename T>
CMatrix<T> CMatrix<T>::operator-(CMatrix<T> matrix){
    if(matrix.iMATLines == this->MATGetLines() && matrix.iMATColumns == this->MATGetLines()) {
        auto toReturn = new CMatrix<T>(this->MATGetLines(), this->MATGetColumns());
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < this->iMATColumns; j++) {
                toReturn->MATSetItemAt(i , j, this->MATGetItemAt(i, j) - matrix.MATGetItemAt(i, j));
            }
        }
        return *toReturn;
    } else throw CMatrixException(MATRIX_EXCEPTION_INCONSISTENT_DIMENSIONS, "Matrix dimensions must be the same for soustraction");
}

//Surcharge addition
template<typename T>
CMatrix<T> CMatrix<T>::operator+(CMatrix<T> matrix){
    if(matrix.iMATLines == this->MATGetLines() && matrix.iMATColumns == this->MATGetLines()) {
        auto toReturn = new CMatrix<T>(this->MATGetLines(), this->MATGetColumns());
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < this->iMATColumns; j++) {
                toReturn->MATSetItemAt(i , j, (this->MATGetItemAt(i, j)) + (matrix.MATGetItemAt(i, j)));
            }
        }
        return *toReturn;
    } else throw CMatrixException(MATRIX_EXCEPTION_INCONSISTENT_DIMENSIONS, "Matrix dimensions must be the same for addition");
}

//Surcharge multiplication par une matrice
template<typename T>
CMatrix<T> CMatrix<T>::operator*(CMatrix<T> matrix){
    if(matrix.iMATColumns == this->MATGetLines() && matrix.iMATLines == this->MATGetColumns()) {
        auto toReturn = new CMatrix<T>(this->MATGetLines(), this->MATGetColumns());
        for (int i = 0; i < this->iMATLines; i++) {
            for (int j = 0; j < matrix.MATGetColumns(); j++) {
                for(int k = 0; k < this->MATGetColumns(); ++k) {
                    toReturn->MATSetItemAt(i , j, toReturn->MATGetItemAt(i, j) + (this->MATGetItemAt(i, k)) * (matrix.MATGetItemAt(k, j)));
                }
            }
        }
        return *toReturn;
    } else {
        throw CMatrixException(MATRIX_EXCEPTION_INCONSISTENT_DIMENSIONS, "Matrix dimensions incompatibles for multiplication");
    }
}

//Surcharge mumtiplication par un nombre
template<typename T>
CMatrix<T> CMatrix<T>::operator*(const double multiplier){
    auto toReturn = new CMatrix<T>(this->MATGetLines(), this->MATGetColumns());
    for(int i = 0; i < this->iMATLines; i++){
        for(int j = 0; j < this->iMATColumns; j++){
            toReturn->MATSetItemAt(i, j, this->MATGetItemAt(i, j) * multiplier);
        }
    }
    return *toReturn;
}

//Surcharge division par un nombre
template<typename T>
CMatrix<T> CMatrix<T>::operator/(const double divider) {
    if(divider != 0) {
        return operator* ((1 / divider));
    } else {
        throw CMatrixException(MATRIX_EXCEPTION_INCONSISTENT_ARITHMETIC, "Dividing by zero is not allowed");
    }
}

template<typename T>
inline T CMatrix<T>::MATGetItemAt(int line, int column){
    return *( *(this->pMATItems + line) + column);
}

template<typename T>
inline void CMatrix<T>::MATSetItemAt(int line, int column, T item){
    *( *(this->pMATItems + line) + column) = item;
}

template<typename T>
inline int CMatrix<T>::MATGetLines(){ return this->iMATLines; }

template<typename T>
inline int CMatrix<T>::MATGetColumns(){ return this->iMATColumns; }

template<typename T>
void CMatrix<T>::MATPrint(){
    for(int i = 0; i < this->iMATLines; i++){
        printf("\n");
        for(int j = 0; j < this->iMATColumns; j++){
            std::cout << this->MATGetItemAt(i, j) << " ";
        }
    }
    printf("\n");
}

#endif //MATRIXEDCPP_CMATRIX_H
