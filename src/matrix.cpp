#include "../includes/matrix.h"
#include <iostream>
#include <cmath>

Matrix::Matrix(unsigned n, unsigned m) : n(n), m(m) {
    for(int i = 0; i < n * m; i++)
        matrix[i] = 0;
}

double Matrix::getValue(unsigned i) {
    if(i > n*m - 1){
        std::cout << "Element out of matrix bounds!" << std::endl;
        exit(0);
    }
    return matrix[i];
}

double Matrix::getValue(unsigned i, unsigned j) {
    return getValue(i*m + j);
}

void Matrix::setValue(double value, unsigned i) {
    if(i > n*m - 1){
        std::cout << "Element out of matrix bounds!" << std::endl;
        exit(0);
    }
    matrix[i] = value;
}

void Matrix::setValue(double value, unsigned i, unsigned j) {
    setValue(value, i*m + j);
}

Matrix Matrix::getTranspose(){
    Matrix mat(m,n);
    for(int line = 0; line < m; line++)
        for(int col = 0; col < n; col++){
            mat.setValue(getValue(col, line), line, col);        
        }

    return mat;
}

Matrix Matrix::operator*(double a){
    for(int i = 0; i < n * m; i++)
        setValue(getValue(i) * a, i);
    return *this;
}

Matrix Matrix::operator/(double a){
    return (*this)*(1.0/a);
}

Matrix Matrix::operator*(Matrix other){
    if(m != other.n) {
        std::cout << "Cannot multiply matrices!" << std::endl;
        exit(0);
    }

    Matrix res(n, other.m);
    for(int line = 0; line < n; line++) {
        for(int col = 0; col < other.m; col++) {
            double temp = 0;
            for(int i = 0; i < m; i++) {
                temp += getValue(line,i) * other.getValue(i,col);
            }
            res.setValue(temp, line, col);
        }
    }

    return res;
}

Vector::Vector(unsigned n) : Matrix(n, 1) {}

Vector Vector::normalize(){
    double temp = 0;
    for(int i = 0; i < n * m; i++){
        temp += getValue(i) * getValue(i);
    }
    temp = std::sqrt(temp);

    for(int i = 0; i < n * m; i++)
        setValue(getValue(i) / temp, i);

    return *this;
}