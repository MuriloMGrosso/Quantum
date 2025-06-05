#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

class Qdit{
protected:
    ComplexVector amplitudes;
public:
    Qdit(unsigned dimension);
    ComplexVector ket();
    ComplexMatrix bra();
    std::complex<double> getAmplitude(unsigned i);
    static ComplexMatrix outerProduct(Qdit q1, Qdit q2);
    static std::complex<double> braket(Qdit q1, Qdit q2);
};

class Qbit : public Qdit{
public:
    Qbit();
    Qbit(std::complex<double> alpha, std::complex<double> beta);
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
};

#endif
