//
// Created by lucas on 31/03/2021.
//

#include "CMatrixException.h"

CMatrixException::CMatrixException(int errorCode, char *message) noexcept {

}

const char *CMatrixException::what() const noexcept {
    return nullptr;
}
