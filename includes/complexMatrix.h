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

#ifndef COMPLEX_MATRIX_H
#define COMPLEX_MATRIX_H

#include <iostream>
#include <complex>

#define MATRIX_MAX_LEN 128                                                          // Maximum number of elements

/*--------------------------------------------------------------------------------------------------------------------------*/

class ComplexMatrix{
protected:
    unsigned n;                                                                     // Number of rows
    unsigned m;                                                                     // Number of columns              
    std::complex<double> matrix[MATRIX_MAX_LEN];                                    // Elements
public:
    ComplexMatrix(unsigned n, unsigned m);                                          // Constructor
    int count();                                                                    // Returns number of elements
    std::complex<double> getTrace();                                                // Returns the trace
    std::complex<double> getValue(unsigned i);                                      // Returns the i-th value
    std::complex<double> getValue(unsigned i, unsigned j);                          // Returns value at line i and column j
    void setValue(std::complex<double> value, unsigned i);                          // Sets the i-th value
    void setValue(std::complex<double> value, unsigned i, unsigned j);              // Sets value at line i and column j
    ComplexMatrix normalize();                                                      // Normalizes (if vector)
    ComplexMatrix getConjugateTranspose();                                          // Returns the conjugate transpose
    ComplexMatrix operator+(ComplexMatrix other);                                   // Sum of matrices
    ComplexMatrix operator-(ComplexMatrix other);                                   // Subtraction of matrices
    ComplexMatrix operator*(ComplexMatrix other);                                   // Matrix multiplication
    ComplexMatrix operator*(std::complex<double> a);                                // Scalar multiplication
    ComplexMatrix operator/(std::complex<double> a);                                // Scalar division
    static ComplexMatrix tensorProduct(ComplexMatrix mat1, ComplexMatrix mat2);     // Tensor product    
    friend std::ostream& operator<<(std::ostream& os,const ComplexMatrix& mat);     // Printing
    friend ComplexMatrix operator*(std::complex<double> a,const ComplexMatrix& mat);// Scalar multiplication
};

#endif
