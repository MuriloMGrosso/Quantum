#ifndef QDIT_H
#define QDIT_H

#include "../includes/matrix.h"

class Qdit{
protected:
    Vector amplitudes;
    Vector ket();
    Matrix bra();
    double getAmplitude(unsigned i);
public:
    Qdit(unsigned dimension);
    static double braket(Qdit q1, Qdit q2);
};

class Qbit : public Qdit{
public:
    Qbit();
    Qbit(double alpha, double beta);
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
};

#endif
