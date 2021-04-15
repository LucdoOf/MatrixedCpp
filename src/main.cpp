#include "CMatrix.h"
#include "CMatrixReader.h"

int main(int argc, char** argv){

    CMatrix<double>** matrixTable;
    for (int i = 1; i < argc; i++) {
        auto reader = new CMatrixReader(argv[i]);
        try {
            matrixTable[i] = reader->MARRead();
        } catch (CMatrixException &exception) {
            std::cout << exception.what() << std::endl;
        }
        delete reader;
    }


    double c = 0;
    std::cout << "Veuillez saisir \"c\"." << std::endl;
    std::cin >>c;
    auto toReturn = new CMatrix<double>(matrixTable[0]->MATGetLines(), matrixTable[0]->MATGetColumns());

    std::cout << "Multiplication de chaque matrices par c" << std::endl;
    for(int i = 0; i < argc; i++){
        *toReturn = *matrixTable[i]*c;
        toReturn->MATPrint();
    }

    std::cout << "Division de chaque matrices par c" << std::endl;
    for(int i = 0; i < argc; i++){
        *toReturn = *matrixTable[i]/c;
        toReturn->MATPrint();
    }

    std::cout << "Addition de chaque matrices entre elles" << std::endl;
    for(int i = 0; i < argc; i++){
        *toReturn = *toReturn + *matrixTable[i];
        toReturn->MATPrint();
    }

    std::cout << "Addition alternée de chaque matrices entre elles" << std::endl;
    for(int i = 0; i < argc; i++){
        *toReturn = *toReturn + ( (*matrixTable[i]) * ((-1)^i) );
        toReturn->MATPrint();
    }

    std::cout << "Produit de chaque matrices entre elles" << std::endl;
    for(int i = 0; i < argc; i++){
        *toReturn = *toReturn * *matrixTable[i];
        toReturn->MATPrint();
    }
}