#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

#define AMPLITUDE_EPSILON 1e-16

class Qdit{
protected:
    ComplexMatrix amplitudes;
    Qdit* entangledQdit;
    void entangle(Qdit &q);
    void breakEntanglement();
public:
    Qdit(unsigned dimension);
    Qdit(ComplexMatrix amplitudes);
    void setAmplitudes(ComplexMatrix amplitudes);
    ComplexMatrix ket();
    ComplexMatrix bra();
    std::complex<double> getAmplitude(unsigned i);
    static void entangle(Qdit &q1, Qdit &q2);
    static ComplexMatrix outerProduct(Qdit q1, Qdit q2);
    static std::complex<double> braket(Qdit q1, Qdit q2);
};

class Qbit : public Qdit{
public:
    Qbit();
    Qbit(ComplexMatrix amplitudes);
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
    double measure(Qbit &q);
    double expectation(Qbit q);
    double getEigenValue(unsigned i);
    ComplexMatrix getEigenVector(unsigned i);
    static HermitianOperator I();
    static HermitianOperator X();
    static HermitianOperator Z();
    static HermitianOperator Y();
    static HermitianOperator H();
    static HermitianOperator PI(unsigned i);
};

#endif
