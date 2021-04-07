#include "CMatrix.h"
#include "CMatrixReader.h"

int main(){
    /**int** a = new int*[2];

    for(int i = 0; i < 2; i++)
        a[i] = new int[2];
        /**for(int j = 0; j < 2; j++){
            a[i][j] = 1;
        }
    }**/
    /**a[0][0] = 1;
    a[0][1] = 1;
    a[1][0] = 0;
    a[1][1] = 1;

    int** b = new int*[2];

    for(int i = 0; i < 2; i++)
        b[i] = new int[2];
    /**for(int j = 0; j < 2; j++){
        a[i][j] = 1;
    }
}**/
    /**b[0][0] = 0;
    b[0][1] = 0;
    b[1][0] = 0;
    b[1][1] = 2;

    auto MAT1 = new CMatrix<int>((int**)a, 2, 2);

    auto MAT2 = new CMatrix<int>((int**)b, 2, 2);

    auto MATResult =  (*MAT2) * (*MAT1);
    //MAT1->MATSetItemAt(0,0, 0);
    //printf("%d",MAT1->MATGetColumns());
    MAT1->MATPrint();
    MATResult.MATPrint();**/
    CMatrixReader reader = CMatrixReader("/home/lucas/Développement/Cpp/Polytech/MatrixedCpp/tests/matrix_1.txt");
    CMatrix<double>* result = reader.MARRead();
    printf("\n%f\n", result->MATGetItemAt(2, 0));
    result->MATPrint();
}