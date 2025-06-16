#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

#define AMPLITUDE_EPSILON 1e-16

class Qdit{
protected:
    ComplexVector amplitudes;
public:
    Qdit(unsigned dimension);
    Qdit(ComplexVector amplitudes);
    ComplexVector ket();
    ComplexMatrix bra();
    std::complex<double> getAmplitude(unsigned i);
    static ComplexMatrix outerProduct(Qdit q1, Qdit q2);
    static std::complex<double> braket(Qdit q1, Qdit q2);
};

class Qbit : public Qdit{
public:
    Qbit();
    Qbit(ComplexVector amplitudes);
    Qbit(std::complex<double> alpha, std::complex<double> beta);
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
};

class HermitianOperator : public ComplexMatrix{
private:
    HermitianOperator(ComplexMatrix matrix);
public:
    double measure(Qdit &q);
    double expectation(Qdit q);
    double getEigenValue(unsigned i);
    ComplexVector getEigenVector(unsigned i);
    static HermitianOperator I();
    static HermitianOperator X();
    static HermitianOperator Z();
    static HermitianOperator Y();
    static HermitianOperator H();
    static HermitianOperator PI(unsigned i);
};

#endif
