#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <iostream>
#include <complex>

#define MATRIX_MAX_LEN 128

class ComplexMatrix{
protected:
    unsigned n;
    unsigned m;
    std::complex<double> matrix[MATRIX_MAX_LEN];
public:
    ComplexMatrix(unsigned n, unsigned m);
    std::complex<double> getTrace();
    std::complex<double> getValue(unsigned i);
    std::complex<double> getValue(unsigned i, unsigned j);
    void setValue(std::complex<double> value, unsigned i);
    void setValue(std::complex<double> value, unsigned i, unsigned j);
    ComplexMatrix getConjugateTranspose();
    ComplexMatrix operator+(ComplexMatrix other);
    ComplexMatrix operator-(ComplexMatrix other);
    ComplexMatrix operator*(ComplexMatrix other);
    ComplexMatrix operator*(std::complex<double> a);
    friend ComplexMatrix operator*(std::complex<double> a, const ComplexMatrix& mat);
    ComplexMatrix operator/(std::complex<double> a);
    friend std::ostream& operator<<(std::ostream& os, const ComplexMatrix& mat);
};

class ComplexVector : public ComplexMatrix{
public:
    ComplexVector(unsigned n);
    ComplexVector normalize();
};

#endif
