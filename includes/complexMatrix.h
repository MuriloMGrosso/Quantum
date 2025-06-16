/*----------------------------------------------------------------------------------
   _____                      _             __  __       _        _      
  / ____|                    | |           |  \/  |     | |      (_)     
 | |     ___  _ __ ___  _ __ | | _____  __ | \  / | __ _| |_ _ __ ___  __
 | |    / _ \| '_ ` _ \| '_ \| |/ _ \ \/ / | |\/| |/ _` | __| '__| \ \/ /
 | |___| (_) | | | | | | |_) | |  __/>  <  | |  | | (_| | |_| |  | |>  < 
  \_____\___/|_| |_| |_| .__/|_|\___/_/\_\ |_|  |_|\__,_|\__|_|  |_/_/\_\
                       | |                                               
                       |_|                                               
----------------------------------------------------------------------------------*/

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
    int count();
    std::complex<double> getTrace();
    std::complex<double> getValue(unsigned i);
    std::complex<double> getValue(unsigned i, unsigned j);
    void setValue(std::complex<double> value, unsigned i);
    void setValue(std::complex<double> value, unsigned i, unsigned j);
    ComplexMatrix normalize();
    ComplexMatrix getConjugateTranspose();
    ComplexMatrix operator+(ComplexMatrix other);
    ComplexMatrix operator-(ComplexMatrix other);
    ComplexMatrix operator*(ComplexMatrix other);
    ComplexMatrix operator*(std::complex<double> a);
    ComplexMatrix operator/(std::complex<double> a);
    friend std::ostream& operator<<(std::ostream& os, const ComplexMatrix& mat);
    friend ComplexMatrix operator*(std::complex<double> a, const ComplexMatrix& mat);
};

#endif
