#include "../includes/quantum.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cmath>

Qdit::Qdit(unsigned dimension) : amplitudes(dimension){
    std::complex<double> temp;
    for(int i = 0; i < dimension; i++){
        std::complex<double> temp(
            (double)std::rand() / RAND_MAX * 2 - 1, 
            (double)std::rand() / RAND_MAX * 2 - 1);
        amplitudes.setValue(temp, i);
    }
    amplitudes.normalize();
}

ComplexVector Qdit::ket(){
    return amplitudes;
}

ComplexMatrix Qdit::bra(){
    return amplitudes.getConjugateTranspose();
}

std::complex<double> Qdit::getAmplitude(unsigned i){
    return amplitudes.getValue(i);
}

ComplexMatrix Qdit::outerProduct(Qdit q1, Qdit q2){
    return q1.ket() * q2.bra(); 
}

std::complex<double> Qdit::braket(Qdit q1, Qdit q2){
    return (q1.bra() * q2.ket()).getValue(0);
}

Qbit::Qbit() : Qdit(2){}
Qbit::Qbit(std::complex<double> alpha, std::complex<double> beta) : Qdit(2){
    if(abs(alpha*alpha + beta*beta - 1.0) > 0.0000000000001){
        std::cout << "ERROR: Invalid qbit amplitudes!" << std::endl;
        exit(0);
    }
    amplitudes.setValue(alpha, 0);
    amplitudes.setValue(beta, 1);
}

Qbit Qbit::zero()   { return Qbit(1, 0); }
Qbit Qbit::one()    { return Qbit(0, 1); }
Qbit Qbit::plus()   { return Qbit(1/std::sqrt(2), 1/std::sqrt(2)); }
Qbit Qbit::minus()  { return Qbit(1/std::sqrt(2),-1/std::sqrt(2)); }