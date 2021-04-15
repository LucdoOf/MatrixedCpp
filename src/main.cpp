#include "CMatrix.h"
#include "CMatrixReader.h"

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

    double c = 0;
    std::cout << "Veuillez saisir un nombre c" << std::endl;
    std::cin >> c;
    auto toReturn = new CMatrix<double>(matrixTable[0]->MATGetLines(), matrixTable[0]->MATGetColumns());
    printf("\n");

    std::cout << "Multiplication de chaque matrices par c:" << std::endl;
    for(int i = 0; i < matrixTableLength; i++){
        *toReturn = *matrixTable[i]*c;
        toReturn->MATPrint();
    }

    std::cout << "Division de chaque matrices par c:" << std::endl;
    for(int i = 0; i < matrixTableLength; i++){
        *toReturn = *matrixTable[i]/c;
        toReturn->MATPrint();
    }

    std::cout << "Addition de chaque matrices entre elles:" << std::endl;
    *toReturn = *matrixTable[0];
    for(int i = 1; i < matrixTableLength; i++){
        *toReturn = *toReturn + *matrixTable[i];
    }
    toReturn->MATPrint();

    std::cout << "Addition alternée de chaque matrices entre elles:" << std::endl;
    *toReturn = *matrixTable[0];
    for(int i = 1; i < matrixTableLength; i++){
        *toReturn = *toReturn + ( (*matrixTable[i]) * ((-1)^i) );
    }
    toReturn->MATPrint();

    std::cout << "Produit de chaque matrices entre elles:" << std::endl;
    *toReturn = *matrixTable[0];
    for(int i = 1; i < matrixTableLength; i++){
        *toReturn = *toReturn * *matrixTable[i];
    }
    toReturn->MATPrint();
}