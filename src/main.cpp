#include "CMatrix.h"
#include "CMatrixReader.h"
#include <iostream>
#include <math.h>

/**
 * Program entry point, run tests with the provided files as arguments
 *
 * @param argc Number of arguments
 * @param argv Argument list, all arguments will be treated as serialized matrix files
 * @return The program exit code
 */
int main(int argc, char** argv){
    try {
        // Check that program arguments are valid
        if (argc <= 1) {
            throw CMatrixException(MATRIX_EXCEPTION_INVALID_PROGRAM_PARAMETERS, "Please provide at least 1 matrix file as program parameter");
        }

        // Initialise the matrix table
        int matrixTableLength = argc - 1;
        auto matrixTable = (CMatrix<double>**) malloc(sizeof(CMatrix<double>) * matrixTableLength);
        for (int i = 1; i < argc; i++) {
            // Read the matrix serialized files
            auto reader = new CMatrixReader(argv[i]);
            matrixTable[i - 1] = reader->MARRead();
            delete reader;
        }

        // Retrieve the input number for tests
        double c = 0;
        printf("\n");
        printf("Veuillez saisir un nombre c: ");
        scanf("%lf", &c);
        printf("\n");

        // Matrices * c
        std::cout << "================= Matrices inchangées: =================" << std::endl;
        for (int i = 0; i < matrixTableLength; i++) {
            printf("\n");
            std::cout << "Matrice " << i + 1 << ": " << std::endl;
            (*matrixTable[i]).MATPrint();
        }

        // Matrices * c
        std::cout << "================= Multiplication de chaque matrices par c: =================" << std::endl;
        for (int i = 0; i < matrixTableLength; i++) {
            printf("\n");
            std::cout << "Matrice " << i + 1 << ": " << std::endl;
            ((*matrixTable[i]) * c).MATPrint();
        }

        // Matrices / c
        std::cout << "================= Division de chaque matrices par c: =================" << std::endl;
        for (int i = 0; i < matrixTableLength; i++) {
            printf("\n");
            std::cout << "Matrice " << i + 1 << " : " << std::endl;
            ((*matrixTable[i]) / c).MATPrint();
        }

        // Matrices sum
        std::cout << "================= Addition de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix1 = *matrixTable[0];
        for (int i = 1; i < matrixTableLength; i++) {
            tempMatrix1 = tempMatrix1 + *matrixTable[i];
        }
        tempMatrix1.MATPrint();

        // Matrices alternate sum
        std::cout << "================= Addition alternée de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix2 = *matrixTable[0];
        for (int i = 1; i < matrixTableLength; i++) {
            tempMatrix2 = tempMatrix2 + ((*matrixTable[i]) * pow(-1, i));
        }
        tempMatrix2.MATPrint();

        // Matrices product
        std::cout << "================= Produit de chaque matrices entre elles: =================" << std::endl;
        auto tempMatrix3 = *matrixTable[0];
        for (int i = 1; i < matrixTableLength; i++) {
            tempMatrix3 = ((tempMatrix3 * *matrixTable[i]));
        }
        tempMatrix3.MATPrint();

        // Matrices transposed
        std::cout << "================= Matrices transposées: =================" << std::endl;
        for (int i = 0; i < matrixTableLength; i++) {
            matrixTable[i]->MATTranspose()->MATPrint();
        }

        // Everything gone well :)
        return 0;
    }
    catch (CMatrixException e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}