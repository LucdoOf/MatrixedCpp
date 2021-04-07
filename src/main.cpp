#include "CMatrix.h"
#include "CMatrixReader.h"

int main(){
    CMatrixReader reader = CMatrixReader("/home/lucas/Développement/Cpp/Polytech/MatrixedCpp/tests/matrix_1.txt");
    reader.MARRead();
}