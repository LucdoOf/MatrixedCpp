//
// Created by lucas on 31/03/2021.
//

#include "CMatrixReader.h"

/**
 * CMatrixReader constructor
 *
 * @param filename Path of the serialized matrix file
 */
CMatrixReader::CMatrixReader(char *filename) {
    this->pMARFilename = strcpy(filename);
}

/**
 * CMatrixReader copy constructor
 *
 * @param reader Reader model
 */
CMatrixReader::CMatrixReader(const CMatrixReader reader) {

}

/**
 * CMatrixReader destructor
 */
CMatrixReader::~CMatrixReader() {
    free(this->pMARFilename);
}

/**
 * Analyze the reader provided file and build a matrix from it
 *
 * @warning Currently the library only supports deserialization of double matrix, if an other type is specified, an
 * exception will be thrown
 * @throw CMatrixException if no file have been found or if the matrix is not of of the type double
 * @return
 */
int CMatrixReader::MARRead() {
    FILE* file = this->MARGetFile();
    if (file) {
        // Buffer used to read the file
        int bufferLength = 255;
        char buffer[bufferLength];
        // Actual number of the file lines that have been analyzed
        int fileLineCounter = 0;
        // Number of lines in the matrix
        int matrixLineCounter = 0;
        // Number of columns in the matrix
        int matrixColumnCounter = 0;
        // Type of the matrix items
        char* matrixType;
        // Number of matrix lines that have been analyzed
        int actualMatrixLineCounter = 0;
        // Number of matrix columns that have been analyzed
        int actualMatrixColumnCounter = 0;
        // buffer will iterate through all of the file lines
        while (fgets(buffer, bufferLength, file) {
            // The buffer treatment will depend on the actual number of lines analyzed
            switch (fileLineCounter) {
                // TypeMatrice=double
                case 0:
                    if (sscanf(buffer, "TypeMatrice=%s", matrixType) != 0) {
                        // Only the double type is supported for now
                        if (matrixType != "double") {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_UNSUPPORTED_TYPE,
                                       "Type " + matrixType + " isn't supported yet by deserialization, please use double only");
                        }
                    } else {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       "Syntax error at line " + fileLineCounter + ", expected \"TypeMatrice=[type]\" got " + buffer);
                    }
                    break;
                // NBLignes=[int]
                case 1:
                    if (sscanf(buffer, "NBLignes=%d", matrixLineCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       "Syntax error at line " + fileLineCounter + ", expected \"NBLignes=[int]\" got " + buffer);
                    }
                    break;
                // NBColonnes=[int]
                case 2:
                    if (sscanf(buffer, "NBColonnes=%d", matrixColumnCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       "Syntax error at line " + fileLineCounter + ", expected \"NBColonnes=[int]\" got " + buffer);
                    }
                    break;
                // Matrice=[
                case 3:
                    if (buffer != "Matrice=[") {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       "Syntax error at line " + fileLineCounter + ", expected \"Matrice=[\" got " + buffer);
                    }
                    break;
                // Lines with double separated with spaces or last line (])
                // There should be the same number of double in a line than the "NBColonnes" field plus,
                // There sould be the same number of lines than the "NBLignes" field
                default:
                    if (buffer == "]") {
                        // If the number of rows declared is inconsistent with the actual number of
                        // rows, we throw an exception
                        if (actualMatrixLineCounter != matrixLineCounter) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_LINE_AMOUNT,
                                       "Syntax error at line " + fileLineCounter + ", Expected " + matrixLineCounter + " amount of lines, "
                                       "declared " actualMatrixLineCounter)
                        }
                    } else {
                        int i = 0;
                        int actualDoubleIndex = 0;
                        char[100] actualDouble;
                        actualMatrixColumnCounter = 0;
                        while (buffer[i] != "\n") {
                            // If the number of columns declared is inconsistent with the actual number of
                            // columns, we throw an exception
                            if (actualMatrixColumnCounter > matrixColumnCounter) {
                                throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_COLUMN_AMOUNT,
                                           "Syntax error at line " + fileLineCounter + ", Expected " + matrixColumnCounter + " amount of columns, "
                                           "declared " actualMatrixColumnCounter)
                            }
                            // If the character is a space, we increment the number of analyzed columns then,
                            // We update the matrix item with the previous analyzed number
                            if (buffer[i] == " ") {
                                actualDouble[actualDoubleIndex] = "\0";
                                double matrixItem = stod(actualDouble);
                                // TODO UPDATE MATRIX ITEM
                                actualDoubleIndex = 0;
                                actualMatrixColumnCounter++;
                            } else {
                                if (buffer[i] == "." || buffer[i] == "-" || isdigit(buffer[i])) {
                                    actualDouble[actualDoubleIndex] = buffer[i];
                                    actualDoubleIndex++;
                                } else {
                                    throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                               "Syntax error at line " + fileLineCounter +
                                               ", Unexpected character " + buffer[i] + ", expected number");
                                }
                            }
                            i++;
                        }
                        actualMatrixLineCounter++;
                    }
                    break;
            }
            // We increment the number of the file lines analyzed
            fileLineCounter++;
        }
    } else {
        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_NO_SUCH_FILE, "No such file " + this->MARGetFilename());
    }
}

FILE* CMatrixReader::MARGetFile() {
    FILE* file = fopen(this->pMARFilename);
    return file;
}

inline int CMatrixReader::MARGetFilename() {

}



