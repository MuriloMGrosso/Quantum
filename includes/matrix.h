#ifndef MATRIX_H
#define MATRIX_H

#define MATRIX_MAX_LEN 128

class Matrix{
protected:
    unsigned n;
    unsigned m;
    double matrix[MATRIX_MAX_LEN];
public:
    Matrix(unsigned n, unsigned m);
    double getValue(unsigned i);
    double getValue(unsigned i, unsigned j);
    void setValue(double value, unsigned i);
    void setValue(double value, unsigned i, unsigned j);
    Matrix getTranspose();
    Matrix operator*(double a);
    Matrix operator/(double a);
    Matrix operator*(Matrix other);
};

class Vector : public Matrix{
public:
    Vector(unsigned n);
    Vector normalize();
};

#endif
