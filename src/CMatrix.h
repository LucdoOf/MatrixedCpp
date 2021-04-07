#ifndef MATRIXEDCPP_CMATRIX_H
#define MATRIXEDCPP_CMATRIX_H

template<typename T = double>
class CMatrix {
    public:
    CMatrix(T** pMATItems, int iMATLines, int iMATColumns);
    CMatrix(const CMatrix<T> &matrix);
    CMatrix(int iMATLines, int iMATColumns);
    ~CMatrix();
    CMatrix<T> MATTranspose(CMatrix<T> matrix);
    CMatrix<T> operator-(const CMatrix<T> &matrix);
    CMatrix<T> operator+(const CMatrix<T> &matrix);
    CMatrix<T> operator*(const CMatrix<T> &matrix);
    CMatrix<T> operator*(const float multiplier);
    CMatrix<T> operator*(const int multiplier);
    CMatrix<T> operator*(const double multiplier);
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


#endif //MATRIXEDCPP_CMATRIX_H
