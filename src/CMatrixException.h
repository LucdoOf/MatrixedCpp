//
// Created by lucas on 31/03/2021.
//

#ifndef MATRIXEDCPP_CMATRIXEXCEPTION_H
#define MATRIXEDCPP_CMATRIXEXCEPTION_H

#include <exception>

class CMatrixException : public std::exception {

public:
    explicit CMatrixException(int errorCode, char* message) noexcept;
    ~CMatrixException() override = default;
    const char* what() const noexcept override;

};


#endif //MATRIXEDCPP_CMATRIXEXCEPTION_H
