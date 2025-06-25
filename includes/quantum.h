#ifndef QDIT_H
#define QDIT_H

#include <complex>
#include "../includes/complexMatrix.h"

#define AMPLITUDE_EPSILON 1e-15

class Qdit;
class Qbit;
class UnitaryOperator;
class CompositeSystem;

class Qdit{
protected:
    ComplexMatrix amplitudes;
    int compositeSystemIndex;
    CompositeSystem* compositeSystem;
public:
    Qdit(unsigned dimension);
    Qdit(ComplexMatrix amplitudes);
    Qdit apply(UnitaryOperator U);
    void setAmplitudes(ComplexMatrix amplitudes);
    void setCompositeSystem(CompositeSystem &compositeSystem, int index);
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
    friend std::ostream& operator<<(std::ostream& os,const Qbit& q);
};

class UnitaryOperator : public ComplexMatrix{
private:
    UnitaryOperator(ComplexMatrix matrix);
public:
    Qdit apply(Qdit &q);
    double measure(Qbit &q);
    double expectation(Qbit q);
    double getEigenValue(unsigned i);
    ComplexMatrix getEigenVector(unsigned i);
    static UnitaryOperator I();
    static UnitaryOperator X();
    static UnitaryOperator Z();
    static UnitaryOperator Y();
    static UnitaryOperator H();
    static UnitaryOperator CNOT();
    static UnitaryOperator Ry(double theta);
};

class CompositeSystem : public Qdit{
private:
    Qbit* q1;
    Qbit* q2;
public:
    CompositeSystem(Qbit &q1, Qbit &q2);
    void colapse();
    void applyCNOT();
    void apply(UnitaryOperator U, int index);
    void apply(UnitaryOperator U1, UnitaryOperator U2);
};

#endif
