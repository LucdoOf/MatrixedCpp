#include "CMatrix.h"
#include "CMatrixReader.h"
#include <iostream>

int main(int argc, char** argv){
    if (argc <= 1) {
        throw CMatrixException(MATRIX_EXCEPTION_INVALID_PROGRAM_PARAMETERS, "Please provide at least 1 matrix file as program parameter");
    }

    int matrixTableLength = argc - 1;
    CMatrix<double>** matrixTable = (CMatrix<double>**) malloc(sizeof(CMatrix<double>) * matrixTableLength);
    for (int i = 1; i < argc; i++) {
        auto reader = new CMatrixReader(argv[i]);
        matrixTable[i-1] = reader->MARRead();
        delete reader;
    }

    int c = 0;
    printf("\n");
    std::cout << "Veuillez saisir un nombre c" << std::endl;
    std::cin >> c;
    printf("\n");

    std::cout << "================= Multiplication de chaque matrices par c: =================" << std::endl;
    for(int i = 0; i < matrixTableLength; i++){
        printf("\n");
        std::cout << "Matrice " << i+1 << ": " << std::endl;
        ((*matrixTable[i]) * c).MATPrint();
    }

    std::cout << "================= Division de chaque matrices par c: =================" << std::endl;
    for(int i = 0; i < matrixTableLength; i++){
        printf("\n");
        std::cout << "Matrice " << i+1 << " : " << std::endl;
        ((*matrixTable[i]) / c).MATPrint();
    }

    std::cout << "================= Addition de chaque matrices entre elles: =================" << std::endl;
    auto tempMatrix1 = new CMatrix<double>(*matrixTable[0]);
    for(int i = 1; i < matrixTableLength; i++){
        *tempMatrix1 = *tempMatrix1 + *matrixTable[i];
    }
    tempMatrix1->MATPrint();

    std::cout << "================= Addition alternée de chaque matrices entre elles: =================" << std::endl;
    auto tempMatrix2 = new CMatrix<double>(*matrixTable[0]);
    for(int i = 1; i < matrixTableLength; i++){
        *tempMatrix2 = *tempMatrix2 + ( (*matrixTable[i]) * ((-1)^i) );
    }
    tempMatrix2->MATPrint();

    std::cout << "================= Produit de chaque matrices entre elles: =================" << std::endl;
    auto tempMatrix3 = new CMatrix<double>(*matrixTable[0]);
    for(int i = 1; i < matrixTableLength; i++){
        *tempMatrix3 = *tempMatrix3 * *matrixTable[i];
    }
    tempMatrix3->MATPrint();
}