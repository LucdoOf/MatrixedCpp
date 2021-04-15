#include "CMatrixException.h"

CMatrixException::CMatrixException(int errorCode, char *message) noexcept {
    this->errorCode = errorCode;
    this->message = message;
}

const char *CMatrixException::what() const noexcept {
    return this->message;
}
