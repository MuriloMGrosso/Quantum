#include "../includes/qbit.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>

Qdit::Qdit(unsigned dimension) : amplitudes(dimension) {
    double temp;
    for(int i = 0; i < dimension; i++){
        temp = (double)std::rand() / RAND_MAX * 2 - 1;
        amplitudes.setValue(temp, i);
    }
    amplitudes.normalize();
}

Vector Qdit::ket(){
    return amplitudes;
}

Matrix Qdit::bra(){
    return amplitudes.getTranspose();
}

double Qdit::getAmplitude(unsigned i) {
    return amplitudes.getValue(i);
}

double Qdit::braket(Qdit q1, Qdit q2) {
    return (q1.bra() * q2.ket()).getValue(0);
}

Qbit::Qbit() : Qdit(2) {}
Qbit::Qbit(double alpha, double beta) : Qdit(2) {
    if(abs(alpha*alpha + beta*beta - 1) > 0.0000000000001){
        std::cout << "Invalid qbit amplitudes!" << std::endl;
        exit(0);
    }
    amplitudes.setValue(alpha, 0);
    amplitudes.setValue(beta, 1);
}

Qbit Qbit::zero()   { return Qbit(1, 0); }
Qbit Qbit::one()    { return Qbit(0, 1); }
Qbit Qbit::plus()   { return Qbit(1/std::sqrt(2), 1/std::sqrt(2)); }
Qbit Qbit::minus()  { return Qbit(1/std::sqrt(2),-1/std::sqrt(2)); }