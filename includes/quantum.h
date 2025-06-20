#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

#define AMPLITUDE_EPSILON 1e-15

class Qdit;
class Qbit;
class UnitaryOperator;

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
public:
    Qbit();
    Qbit(ComplexMatrix amplitudes);
    Qbit(std::complex<double> alpha, std::complex<double> beta);
    void colapse(ComplexMatrix amplitudes);
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
};

class UnitaryOperator : public ComplexMatrix{
private:
    UnitaryOperator(ComplexMatrix matrix);
public:
    Qbit apply(Qbit &q);
    double measure(Qbit &q);
    double expectation(Qbit q);
    double getEigenValue(unsigned i);
    ComplexMatrix getEigenVector(unsigned i);
    static UnitaryOperator I();
    static UnitaryOperator X();
    static UnitaryOperator Z();
    static UnitaryOperator Y();
    static UnitaryOperator H();
    static UnitaryOperator Ry(double theta);
};

#endif
