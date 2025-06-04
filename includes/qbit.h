#ifndef QBIT_H
#define QBIT_H

class Qbit{
private:
    double alpha;
    double beta;
protected:
    double getAlpha();
    double getBeta();
public:
    Qbit();
    Qbit(double alpha, double beta);
    void print();
    static Qbit zero();
    static Qbit one();
    static Qbit plus();
    static Qbit minus();
    static double braket(Qbit q1, Qbit q2);
};

#endif
