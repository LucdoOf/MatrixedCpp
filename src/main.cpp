#include "CMatrix.h"

int main(){
    int** a = new int*[2];

    for(int i = 0; i < 2; i++){
        a[i] = new int[2];
        for(int j = 0; j < 2; j++){
            a[i][j] = 1;
        }
    }

    auto *MAT1 = new CMatrix<int>((int**)a, 2, 2);

    auto *MAT2 = new CMatrix<int>(*MAT1);

    auto *MATResult = new CMatrix<int>(2,2);
    *MATResult = *MAT1 + *MAT2;
    MATResult->MATPrint();
}