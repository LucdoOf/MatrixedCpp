#ifndef MATRIXEDCPP_CMATRIX_H
#define MATRIXEDCPP_CMATRIX_H

#include <malloc.h>
#include <iostream>
#include "CMatrixException.h"
#include "defines.h"

/**
 * CMatrix class
 *
 * This class represents an arithmetic matrix containing objects of type T
 * The CMatrix class overload several operators to ease the use of matrices and also includes a few public methods
 *
 * @warning Overloaded operators are not safe if the type T don't overload them too
 * @tparam T Template type, be careful to use a correct type that support operation such as multiplication if you want
 * to use them with the CMatrix class
 */
template<typename T>
class CMatrix {

public:
    /**
     * CMatrix constructor
     *
     * @param pMATItems 2D array that represents the matrix items
     * @param iMATLines Number of lines of the matrix
     * @param iMATColumns Number of columns of the matrix
     * @warning The matrix will free the provided array after destruction
     */
    CMatrix(T** pMATItems, int iMATLines, int iMATColumns);
    /**
     * CMatrix copy constructor
     *
     * @param matrix CMatrix model
     */
    CMatrix(const CMatrix<T> &matrix);
    /**
     * CMatrix constructor
     *
     * The 2D array of items will be allocated automatically with no default value
     *
     * @param iMATLines Number of lines of the matrix
     * @param iMATColumns Number of columns of the matrix
     */
    CMatrix(int iMATLines, int iMATColumns);
    /**
     * CMatrixReader destructor
     *
     * Free the 2D array of items
     */
    ~CMatrix();
    /**
     * Transpose the matrix into a new one without modifying the caller object
     *
     * @return The transposed matrix
     */
    CMatrix<T> MATTranspose();
    /**
     * CMatrix minus CMatrix operator
     *
     * Subtract all of the matrix items by the corresponding matrix items without modifying the caller object
     *
     * @param matrix Matrix to subtract with
     * @return Caller matrix minus provided matrix into a new matrix
     */
    CMatrix<T> operator-(CMatrix<T> matrix);
    /**
     * CMatrix plus CMatrix operator
     *
     * Add all of the matrix items by the corresponding matrix items without modifying the caller object
     *
     * @param matrix Matrix to add up with
     * @return Caller matrix minus provided matrix into a new matrix
     */
    CMatrix<T> operator+(CMatrix<T> matrix);
    /**
     * CMatrix times CMatrix operator
     *
     * Multiply all of the matrix items by the corresponding matrix items without modifying the caller object
     *
     * @param matrix Matrix to multiply with
     * @return Caller matrix times provided matrix into a new matrix
     */
    CMatrix<T> operator*(CMatrix<T> matrix);
    /**
     * CMatrix times number operator
     *
     * Multiply all of the matrix items by the provided number without modifying the caller object
     *
     * @param multiplier Number to multiply with
     * @return Caller matrix times provided number into a new matrix
     */
    CMatrix<T> operator*(double multiplier);
    /**
     * CMatrix divided by number operator
     *
     * Divide all of the matrix items by the provided number without modifying the caller object
     *
     * @param divider Number to divide with
     * @return Caller matrix divided by the provided number into a new matrix
     */
    CMatrix<T> operator/(double divider);
    /**
     * Retrieves the item at the provided line and at the provided column
     *
     * @param line Item line
     * @param column Item column
     * @return The item at the provided line and at the provided column
     */
    T MATGetItemAt(int line, int column);
    /**
     * Set the item at the given line and column to the provided value
     *
     * @param line Item line
     * @param column Item column
     * @param item Item new value
     */
    void MATSetItemAt(int line, int column, T item);
    /**
     * Retrieves the amount of lines in the matrix
     *
     * @return The amount of lines in the matrix
     */
    int MATGetLines();
    /**
     * Retrieves the amount of columns in the matrix
     *
     * @return The amount of columns in the matrix
     */
    int MATGetColumns();
    /**
     * Print the content of the matrix into the standard output
     */
    void MATPrint();

protected:
    /**
     * Amount of lines in the matrix
     */
    int iMATLines;
    /**
     * Amount of columns in the matrix
     */
    int iMATColumns;
    /**
     * 2D array that represents the matrix items
     */
    T** pMATItems;

};

/**
 * CMatrix constructor
 *
 * @param pMATItems 2D array that represents the matrix items
 * @param iMATLines Number of lines of the matrix
 * @param iMATColumns Number of columns of the matrix
 * @warning The matrix will free the provided array after destruction
 */
template<typename T>
CMatrix<T>::CMatrix(T** pMATItems, int iMATLines, int iMATColumns){
    this->pMATItems = pMATItems;
    this->iMATLines = iMATLines;
    this->iMATColumns = iMATColumns;
}

/**
 * CMatrix copy constructor
 *
 * @param matrix CMatrix model
 */
template<typename T>
CMatrix<T>::CMatrix(const CMatrix<T> &matrix){
    this->iMATColumns = matrix.iMATColumns;
    this->iMATLines = matrix.iMATLines;
    this->pMATItems = (T**) malloc(sizeof(T*)*iMATLines);
    // Maloc items
    for(int h = 0; h < iMATLines; h++){
        this->pMATItems[h] = (T *) malloc(sizeof(T*) * iMATColumns);
    }
    // Update items
    for(int i = 0; i < iMATLines; i++){
        for(int j = 0; j < iMATColumns; j++){
            this->MATSetItemAt(i, j, matrix.pMATItems[i][j]);
        }
    }
}

/**
 * CMatrix constructor
 *
 * The 2D array of items will be allocated automatically with no default value
 *
 * @param iMATLines Number of lines of the matrix
 * @param iMATColumns Number of columns of the matrix
 */
template<typename T>
CMatrix<T>::CMatrix(int iMATLines, int iMATColumns) {
    this->iMATLines = iMATLines;
    this->iMATColumns = iMATColumns;
    this->pMATItems = (T**) malloc(sizeof(T*)*iMATLines);
    for(int h = 0; h < iMATLines; h++){
        this->pMATItems[h] = (T *) malloc(sizeof(T*) * iMATColumns);
    }
}

/**
 * CMatrixReader destructor
 *
 * Free the 2D array of items
 */
template<typename T>
CMatrix<T>::~CMatrix(){
    for(int i = 0; i < iMATLines; i++){
        free(this->pMATItems[i]);
    }
    free(this->pMATItems);
}

/**
 * Transpose the matrix into a new one without modifying the caller object
 *
 * @return The transposed matrix
 */
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

/**
 * CMatrix minus CMatrix operator
 *
 * Subtract all of the matrix items by the corresponding matrix items without modifying the caller object
 *
 * @param matrix Matrix to subtract with
 * @return Caller matrix minus provided matrix into a new matrix
 */
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

/**
 * CMatrix plus CMatrix operator
 *
 * Add all of the matrix items by the corresponding matrix items without modifying the caller object
 *
 * @param matrix Matrix to add up with
 * @return Caller matrix minus provided matrix into a new matrix
 */
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

/**
 * CMatrix times CMatrix operator
 *
 * Multiply all of the matrix items by the corresponding matrix items without modifying the caller object
 *
 * @param matrix Matrix to multiply with
 * @return Caller matrix times provided matrix into a new matrix
 */
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

/**
 * CMatrix times number operator
 *
 * Multiply all of the matrix items by the provided number without modifying the caller object
 *
 * @param multiplier Number to multiply with
 * @return Caller matrix times provided number into a new matrix
 */
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

/**
 * CMatrix divided by number operator
 *
 * Divide all of the matrix items by the provided number without modifying the caller object
 *
 * @param divider Number to divide with
 * @return Caller matrix divided by the provided number into a new matrix
 */
template<typename T>
CMatrix<T> CMatrix<T>::operator/(const double divider) {
    if(divider != 0) {
        return operator* ((1 / divider));
    } else {
        throw CMatrixException(MATRIX_EXCEPTION_INCONSISTENT_ARITHMETIC, "Dividing by zero is not allowed");
    }
}

/**
 * Retrieves the item at the provided line and at the provided column
 *
 * @param line Item line
 * @param column Item column
 * @return The item at the provided line and at the provided column
 */
template<typename T>
inline T CMatrix<T>::MATGetItemAt(int line, int column){
    return *( *(this->pMATItems + line) + column);
}

/**
 * Set the item at the given line and column to the provided value
 *
 * @param line Item line
 * @param column Item column
 * @param item Item new value
 */
template<typename T>
inline void CMatrix<T>::MATSetItemAt(int line, int column, T item){
    *( *(this->pMATItems + line) + column) = item;
}

/**
 * Retrieves the amount of lines in the matrix
 *
 * @return The amount of lines in the matrix
 */
template<typename T>
inline int CMatrix<T>::MATGetLines(){ return this->iMATLines; }

/**
 * Retrieves the amount of columns in the matrix
 *
 * @return The amount of columns in the matrix
 */
template<typename T>
inline int CMatrix<T>::MATGetColumns(){ return this->iMATColumns; }

/**
 * Print the content of the matrix into the standard output
 */
template<typename T>
void CMatrix<T>::MATPrint(){
    std::cout.precision(4);
    for(int i = 0; i < this->iMATLines; i++){
        printf("\n");
        for(int j = 0; j < this->iMATColumns; j++){
            std::cout << std::fixed << this->MATGetItemAt(i, j) << " ";
        }
    }
    printf("\n\n");
}

#endif //MATRIXEDCPP_CMATRIX_H
