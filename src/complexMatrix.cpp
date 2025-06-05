#include "../includes/complexMatrix.h"
#include <iostream>
#include <cmath>

ComplexMatrix::ComplexMatrix(unsigned n, unsigned m) : n(n), m(m){
    for(int i = 0; i < n * m; i++)
        matrix[i] = std::complex<double>();
}

std::complex<double> ComplexMatrix::getTrace(){
    if(m != n){
        std::cout << "ERROR: Cannot get trace from a non-squared matrix!" << std::endl;
        exit(0);
    }

    std::complex<double> trace;
    for(int i = 0; i < m; i++)
        trace += getValue(i,i);
    return trace;
}

std::complex<double> ComplexMatrix::getValue(unsigned i){
    if(i > n*m - 1){
        std::cout << "ERROR: Element out of matrix bounds!" << std::endl;
        exit(0);
    }
    return matrix[i];
}

std::complex<double> ComplexMatrix::getValue(unsigned i, unsigned j){
    return getValue(i*m + j);
}

void ComplexMatrix::setValue(std::complex<double> value, unsigned i){
    if(i > n*m - 1){
        std::cout << "ERROR: Element out of matrix bounds!" << std::endl;
        exit(0);
    }
    matrix[i] = value;
}

void ComplexMatrix::setValue(std::complex<double> value, unsigned i, unsigned j){
    setValue(value, i*m + j);
}

ComplexMatrix ComplexMatrix::getConjugateTranspose(){
    ComplexMatrix mat(m,n);
    for(int line = 0; line < m; line++)
        for(int col = 0; col < n; col++){
            mat.setValue(std::conj(getValue(col, line)), line, col);        
        }

    return mat;
}

ComplexMatrix ComplexMatrix::operator+(ComplexMatrix other){
    if(n != other.n || m != other.m){
        std::cout << "ERROR: Cannot add matrices!" << std::endl;
        exit(0);
    }

    ComplexMatrix res(n, m);
    for(int i = 0; i < n*m; i++)
        res.setValue(getValue(i) + other.getValue(i), i);
    return res;
}

ComplexMatrix ComplexMatrix::operator-(ComplexMatrix other){
    if(n != other.n || m != other.m){
        std::cout << "ERROR: Cannot subtract matrices!" << std::endl;
        exit(0);
    }

    ComplexMatrix res(n, m);
    for(int i = 0; i < n*m; i++)
        res.setValue(getValue(i) - other.getValue(i), i);
    return res;
}

ComplexMatrix ComplexMatrix::operator*(ComplexMatrix other){
    if(m != other.n){
        std::cout << "ERROR: Cannot multiply matrices!" << std::endl;
        exit(0);
    }

    ComplexMatrix res(n, other.m);
    for(int line = 0; line < n; line++){
        for(int col = 0; col < other.m; col++){
            std::complex<double> temp;
            for(int i = 0; i < m; i++){
                temp += getValue(line,i) * other.getValue(i,col);
            }
            res.setValue(temp, line, col);
        }
    }

    return res;
}

ComplexMatrix ComplexMatrix::operator*(std::complex<double> a){
    ComplexMatrix res(n,m);
    for(int i = 0; i < n * m; i++)
        res.setValue(getValue(i) * a, i);
    return res;
}

ComplexMatrix operator*(std::complex<double> a, const ComplexMatrix& mat){
    ComplexMatrix res(mat.n,mat.m);
    for(int i = 0; i < mat.n * mat.m; i++)
        res.setValue(mat.matrix[i] * a, i);
    return res;
}

ComplexMatrix ComplexMatrix::operator/(std::complex<double> a){
    return (*this)*(1.0/a);
}

std::ostream& operator<<(std::ostream& os, const ComplexMatrix& mat){
    for(int i = 0; i < mat.n; i++){
        os << (mat.n == 1 ? "(" : i == mat.n - 1 ? " \\" : i == 0 ? " /" : "| ");
        for(int j = 0; j < mat.m; j++)
            os << mat.matrix[i*mat.m + j] << (j == mat.m - 1 ? "" : " ");
        os << (mat.n == 1 ? ")" : i == mat.n - 1 ? "/" : i == 0 ? "\\" : " |") << std::endl;
    }
    return os;
}

ComplexVector::ComplexVector(unsigned n) : ComplexMatrix(n, 1){}

ComplexVector ComplexVector::normalize(){
    std::complex<double> temp;
    for(int i = 0; i < n * m; i++){
        temp += getValue(i) * getValue(i);
    }
    temp = std::sqrt(temp);

    for(int i = 0; i < n * m; i++)
        setValue(getValue(i) / temp, i);

    return *this;
}