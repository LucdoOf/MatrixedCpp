#include "CMatrixReader.h"
#include "CMatrixException.h"

/**
 * CMatrixReader default constructor
 *
 * @param filename Path of the serialized matrix file
 */
CMatrixReader::CMatrixReader(const char *filename) {
    this->pMARFilename = filename;
}

/**
 * CMatrixReader copy constructor
 *
 * @param reader Reader model
 */
CMatrixReader::CMatrixReader(const CMatrixReader &reader) {
    this->pMARFilename = reader.pMARFilename;
}

/**
 * Close the reader file if it opened then destroy it
 */
CMatrixReader::~CMatrixReader() {
    if (this->pMARFile != nullptr) {
        fclose(this->pMARFile);
        free(this->pMARFile);
    }
}

/**
 * Analyze the reader provided file and build a matrix from it
 *
 * @warning Currently the library only supports deserialization of double matrix, if an other type is specified, an
 * exception will be thrown
 * @throw CMatrixException if no file have been found, if the matrix is not of of the type double or the file is mal-formed
 * @return A fresh new matrix initialized and filled following the reader file instructions
 */
CMatrix<double>* CMatrixReader::MARRead() {
    FILE* file = this->MARGetFile();
    if (file) {
        // Current matrix
        CMatrix<double> *matrix;
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
        char matrixType[50];
        // Number of matrix lines that have been analyzed
        int actualMatrixLineCounter = 0;
        // Number of matrix columns that have been analyzed
        int actualMatrixColumnCounter = 0;
        // buffer will iterate through all of the file lines
        while (fgets(buffer, bufferLength, file)) {
            // Increment the number of the file lines analyzed
            fileLineCounter++;
            // The buffer treatment will depend on the actual number of lines analyzed
            switch (fileLineCounter) {
                // TypeMatrice=double
                case 1:
                    if (sscanf(buffer, "TypeMatrice=%s", matrixType) == 1) {
                        // Only the double type is supported for now
                        if (strcmp(matrixType, "double") != 0) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_UNSUPPORTED_TYPE,
                                       strMultiCat(3, "Type ", matrixType, " isn't supported yet by deserialization, please use double only"));
                        }
                    } else {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       strMultiCat(4, "Syntax error at line ", itoa(fileLineCounter), ", expected \"TypeMatrice=[type]\" got ", buffer));
                    }
                    break;
                // NBLignes=[int]
                case 2:
                    if (sscanf(buffer, "NBLignes=%d", &matrixLineCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       strMultiCat(4, "Syntax error at line ", itoa(fileLineCounter), ", expected \"NBLignes=[int]\" got ", buffer));
                    }
                    break;
                // NBColonnes=[int]
                case 3:
                    if (sscanf(buffer, "NBColonnes=%d", &matrixColumnCounter) == 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       strMultiCat(4, "Syntax error at line ", itoa(fileLineCounter), ", expected \"NBColonnes=[int]\" got ", buffer));
                    }
                    break;
                // Matrice=[
                case 4:
                    if (strcmp(buffer, "Matrice=[\n") != 0) {
                        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                       strMultiCat(4, "Syntax error at line ", itoa(fileLineCounter), R"(, expected "Matrice=[\n" got )", buffer));
                    }
                    matrix = new CMatrix<double>(matrixLineCounter, matrixColumnCounter);
                    break;
                // Lines with double separated with spaces or last line (])
                // There should be the same number of double in a line than the "NBColonnes" field plus,
                // There sould be the same number of lines than the "NBLignes" field
                default:
                    if (strcmp(buffer, "]") == 0) {
                        // If the number of rows declared is inconsistent with the actual number of
                        // rows, we throw an exception
                        if (actualMatrixLineCounter != matrixLineCounter) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_LINE_AMOUNT,
                                       strMultiCat(6, "Syntax error at line ", itoa(fileLineCounter), ", Expected an amount of ", itoa(matrixLineCounter), " lines, "
                                       "declared ", itoa(actualMatrixLineCounter)));
                        } else {
                            return matrix;
                        }
                    } else {
                        int i = 0;
                        int actualDoubleIndex = 0;
                        char actualDouble[100];
                        actualMatrixColumnCounter = 1;
                        while (buffer[i] != '\n') {
                            // If the number of columns declared is inconsistent with the actual number of
                            // columns, we throw an exception
                            if (actualMatrixColumnCounter > matrixColumnCounter) {
                                throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_COLUMN_AMOUNT,
                                           strMultiCat(6, "Syntax error at line ", itoa(fileLineCounter),  ", Expected an amount of ", itoa(matrixColumnCounter), " columns, "
                                           "declared ", itoa(actualMatrixColumnCounter)));
                            }
                            // If the character is a space, we increment the number of analyzed columns then,
                            // We update the matrix item with the previous analyzed number
                            if (buffer[i] == ' ') {
                                actualDouble[actualDoubleIndex] = '\0';
                                double matrixItem = atof(actualDouble);
                                matrix->MATSetItemAt(actualMatrixLineCounter, actualMatrixColumnCounter, matrixItem);
                                actualDoubleIndex = 0;
                                actualMatrixColumnCounter++;
                            } else {
                                if (buffer[i] == '.' || buffer[i] == '-' || isdigit(buffer[i])) {
                                    actualDouble[actualDoubleIndex] = buffer[i];
                                    actualDoubleIndex++;
                                } else {
                                    char wrongChar[2] = {buffer[i], '\0'};
                                    throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT,
                                               strMultiCat(5, "Syntax error at line ", itoa(fileLineCounter),
                                               ", Unexpected character ", wrongChar, ", expected number"));
                                }
                            }
                            i++;
                        }
                        if (actualMatrixColumnCounter < matrixColumnCounter) {
                            throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_INCONSISTENT_COLUMN_AMOUNT,
                                                   strMultiCat(6, "Syntax error at line ", itoa(fileLineCounter),  ", Expected an amount of ", itoa(matrixColumnCounter), " columns, "
                                                          "declared ", itoa(actualMatrixColumnCounter)));
                        }
                        actualMatrixLineCounter++;
                    }
                    break;
            }
        }
        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_WRONG_FILE_FORMAT, "File is not complete");
    } else {
        throw CMatrixException(MATRIX_EXCEPTION_DESERIALIZATION_NO_SUCH_FILE, strMultiCat(2, "No such file ", this->MARGetFilename()));
    }
}

/**
 * Opens a file stream if the provided file has not been opened yet,
 * then returns the provided file as a FILE pointer
 *
 * @return
 */
FILE* CMatrixReader::MARGetFile() {
    if (this->pMARFile == nullptr) {
        this->pMARFile = fopen(this->pMARFilename, "r");
    }
    return this->pMARFile;
}

/**
 * Retrieves the reader provided file name
 *
 * @return The reader provided file name
 */
inline const char* CMatrixReader::MARGetFilename() {
    return this->pMARFilename;
}

