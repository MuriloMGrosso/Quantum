/*----------------------------------------------------------------------------------------------------------------------------
   _____                      _             __  __       _        _                 |
  / ____|                    | |           |  \/  |     | |      (_)                | COMPLEX MATRIX:
 | |     ___  _ __ ___  _ __ | | _____  __ | \  / | __ _| |_ _ __ ___  __           | A simple representation of a matematical
 | |    / _ \| '_ ` _ \| '_ \| |/ _ \ \/ / | |\/| |/ _` | __| '__| \ \/ /           | complex matrix and its basic functions.
 | |___| (_) | | | | | | |_) | |  __/>  <  | |  | | (_| | |_| |  | |>  <            | 
  \_____\___/|_| |_| |_| .__/|_|\___/_/\_\ |_|  |_|\__,_|\__|_|  |_/_/\_\           |
                       | |                                                          | By Murilo M. Grosso
                       |_|                                                          |                                                                                                   |
----------------------------------------------------------------------------------------------------------------------------*/

#include "../includes/complexMatrix.h"
#include <iostream>
#include <iomanip>
#include <cmath>

ComplexMatrix::ComplexMatrix(unsigned n, unsigned m) : n(n), m(m){
    for(int i = 0; i < n * m; i++)
        matrix[i] = std::complex<double>();
}

int ComplexMatrix::count(){ return n*m; }

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
        std::cout << "ERROR: Index out of matrix bounds!" << std::endl;
        exit(0);
    }
    return matrix[i];
}

std::complex<double> ComplexMatrix::getValue(unsigned i, unsigned j){
    return getValue(i*m + j);
}

void ComplexMatrix::setValue(std::complex<double> value, unsigned i){
    if(i > n*m - 1){
        std::cout << "ERROR: Index out of matrix bounds!" << std::endl;
        exit(0);
    }
    matrix[i] = value;
}

void ComplexMatrix::setValue(std::complex<double> value, unsigned i, unsigned j){
    setValue(value, i*m + j);
}

ComplexMatrix ComplexMatrix::normalize(){
    if(m != 1 && n != 1){
        std::cout << "ERROR: Cannot normalize a non-vector matrix!" << std::endl;
        exit(0);
    }

    std::complex<double> temp;
    for(int i = 0; i < n * m; i++){
        temp += std::pow(std::abs(getValue(i)), 2);
    }
    temp = std::sqrt(temp);

    for(int i = 0; i < n * m; i++)
        setValue(getValue(i) / temp, i);

    // First element as positive value
    (*this) = (*this) * (getValue(0).real() < 0 ? -1 : 1);

    return (*this);
}

ComplexMatrix ComplexMatrix::getConjugateTranspose(){
    ComplexMatrix mat(m,n);
    for(int line = 0; line < m; line++)
        for(int col = 0; col < n; col++)
            mat.setValue(std::conj(getValue(col, line)), line, col);        
    return mat;
}

ComplexMatrix ComplexMatrix::operator+(ComplexMatrix other){
    if(n != other.n || m != other.m){
        std::cout << "ERROR: Cannot add matrices with different sizes!" << std::endl;
        exit(0);
    }

    ComplexMatrix res(n, m);
    for(int i = 0; i < n*m; i++)
        res.setValue(getValue(i) + other.getValue(i), i);
    return res;
}

ComplexMatrix ComplexMatrix::operator-(ComplexMatrix other){
    if(n != other.n || m != other.m){
        std::cout << "ERROR: Cannot subtract matrices with different sizes!" << std::endl;
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

ComplexMatrix ComplexMatrix::tensorProduct(ComplexMatrix mat1, ComplexMatrix mat2){
    int n = mat1.n * mat2.n;
    int m = mat1.m * mat2.m;
    ComplexMatrix mat(n, m);
    for(int line = 0; line < n; line++){
        for(int col = 0; col < m; col++){
            mat.setValue(mat1.getValue(line/mat2.n,col/mat2.m)*mat2.getValue(line%mat2.n,col%mat2.m), line, col);     
        }
    }
    return mat;
}

std::ostream& operator<<(std::ostream& os, const ComplexMatrix& mat){
    for(int i = 0; i < mat.n; i++){
        os << (mat.n == 1 ? "(" : i == mat.n - 1 ? " \\" : i == 0 ? " /" : "| ");
        for(int j = 0; j < mat.m; j++){
            std::complex<double> c = mat.matrix[i*mat.m + j];
            os << std::setw(6) << std::fixed << std::setprecision(3) << c.real() << (c.imag() < 0 ? "-" : "+");
            os << std::setw(5) << std::fixed << std::setprecision(3) << std::abs(c.imag()) << "i";
            os << (j == mat.m - 1 ? "" : " ");
        }
        os << (mat.n == 1 ? ")" : i == mat.n - 1 ? "/" : i == 0 ? "\\" : " |") << std::endl;
    }
    return os;
}