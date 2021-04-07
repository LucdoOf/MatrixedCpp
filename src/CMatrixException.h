//
// Created by lucas on 31/03/2021.
//

#ifndef MATRIXEDCPP_CMATRIXEXCEPTION_H
#define MATRIXEDCPP_CMATRIXEXCEPTION_H

class CMatrixException : public std::exception {

    explicit Exception(int errorCode, const char* message) noexcept;
    virtual ~Exception() = default;
    virtual const char* what() const noexcept override;

};


#endif //MATRIXEDCPP_CMATRIXEXCEPTION_H
