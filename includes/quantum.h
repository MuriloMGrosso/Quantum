#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

#define AMPLITUDE_EPSILON 1e-15

class Qdit{
protected:
    ComplexMatrix amplitudes;
public:
    Qdit(unsigned dimension);
    Qdit(ComplexMatrix amplitudes);
    void setAmplitudes(ComplexMatrix amplitudes);
    ComplexMatrix ket();
    ComplexMatrix bra();
    std::complex<double> getAmplitude(unsigned i);
    static ComplexMatrix outerProduct(Qdit q1, Qdit q2);
    static std::complex<double> braket(Qdit q1, Qdit q2);
};

class Qbit : public Qdit{
private:
    Qbit *entangledQbit;
public:
    Qbit();
    Qbit(ComplexMatrix amplitudes);
    Qbit(std::complex<double> alpha, std::complex<double> beta);
    void colapse(ComplexMatrix amplitudes);
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
    static void entangle(Qbit &q1, Qbit &q2);
};

class HermitianOperator : public ComplexMatrix{
private:
    HermitianOperator(ComplexMatrix matrix);
public:
    Qbit apply(Qbit &q);
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
    static HermitianOperator RY(double theta);
};

#endif
