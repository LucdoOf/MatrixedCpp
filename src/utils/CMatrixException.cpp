#include "CMatrixException.h"

/**
 * CMatrixException constructor
 *
 * @see defines.h For the list of available error codes
 * @param errorCode Error code used to identify the exception
 * @param message Message describing the exception
 */
CMatrixException::CMatrixException(int errorCode, char *message) noexcept {
    this->errorCode = errorCode;
    this->message = message;
}

/**
 * @inheritDoc
 */
const char *CMatrixException::what() const noexcept {
    char* toReturn = (char*) malloc(sizeof(this->message) + sizeof(char) * 5);
    sprintf(toReturn, "%d: %s", this->errorCode, this->message);
    return toReturn;
}
