#include "../includes/quantum.h"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <cmath>

Qdit::Qdit(unsigned dimension) : amplitudes(dimension, 1){
    std::complex<double> temp;
    for(int i = 0; i < dimension; i++){
        std::complex<double> temp(
            (double)std::rand() / RAND_MAX * 2 - 1, 
            (double)std::rand() / RAND_MAX * 2 - 1);
        amplitudes.setValue(temp, i);
    }
    amplitudes.normalize();
}

Qdit::Qdit(ComplexMatrix amplitudes) : amplitudes(amplitudes){
    setAmplitudes(amplitudes); 
}

void Qdit::setAmplitudes(ComplexMatrix amplitudes){
    double sum = 0;
    for(int i = 0; i < amplitudes.count(); i++)
        sum += std::pow(std::abs(amplitudes.getValue(i)), 2);
    if(sum - 1.0 > AMPLITUDE_EPSILON){
        std::cout << "ERROR: Invalid qdit amplitudes!" << std::endl;
        exit(0);
    }
    this->amplitudes = amplitudes;
    
    if(entangledQdit){
        entangledQdit->amplitudes = amplitudes;
        entangledQdit->breakEntanglement();
        breakEntanglement();
    }
}

ComplexMatrix Qdit::ket(){
    return amplitudes;
}

ComplexMatrix Qdit::bra(){
    return amplitudes.getConjugateTranspose();
}

std::complex<double> Qdit::getAmplitude(unsigned i){
    return amplitudes.getValue(i);
}

void Qdit::entangle(Qdit &q){
    entangledQdit = &q;
}

void Qdit::breakEntanglement(){
    entangledQdit = NULL;
}

void Qdit::entangle(Qdit &q1, Qdit &q2){
    if(q1.amplitudes.count() != q2.amplitudes.count()){
        std::cout << "ERROR: Cannot entangle these Qdits!" << std::endl;
        exit(0);
    }
    Qdit temp(q1.amplitudes.count());
    q1 = temp;
    q2 = temp;
    q1.entangle(q2);
    q2.entangle(q1);
}

ComplexMatrix Qdit::outerProduct(Qdit q1, Qdit q2){
    return q1.ket() * q2.bra(); 
}

std::complex<double> Qdit::braket(Qdit q1, Qdit q2){
    return (q1.bra() * q2.ket()).getValue(0);
}

Qbit::Qbit() : Qdit(2){}
Qbit::Qbit(ComplexMatrix amplitudes) : Qdit(amplitudes){
    if(amplitudes.count() != 2){
        std::cout << "ERROR: Invalid qbit amplitudes!" << std::endl;
        exit(0);
    }    
}
Qbit::Qbit(std::complex<double> alpha, std::complex<double> beta) : Qdit(2){
    if(std::pow(std::abs(alpha), 2) + std::pow(std::abs(beta), 2) - 1.0 > AMPLITUDE_EPSILON){
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

HermitianOperator::HermitianOperator(ComplexMatrix matrix) : ComplexMatrix(matrix){}

double HermitianOperator::measure(Qbit &q){
    double r = (double)std::rand() / RAND_MAX;
    double p = std::pow(std::abs((getEigenVector(0).getConjugateTranspose()*q.ket()).getValue(0)),2);
    if(p >= r){
        q.setAmplitudes(getEigenVector(0));
        return getEigenValue(0);
    }
    q.setAmplitudes(getEigenVector(1));
    return getEigenValue(1);
}

double HermitianOperator::getEigenValue(unsigned i){
    if(std::abs((int)i) > 2){
        std::cout << "ERROR: Eigen value index out off operator bounds!" << std::endl;
        exit(0);
    }
    std::complex<double> p = getValue(0)*getValue(3) - getValue(1)*getValue(2);
    std::complex<double> m = getTrace()/2.0;
    return (m + (1.0 - i*2) * std::sqrt(m*m - p)).real(); 
}

ComplexMatrix HermitianOperator::getEigenVector(unsigned i){
    ComplexMatrix eigenVector(2,1);
    double lambda = getEigenValue(i);
    std::complex<double> a = getValue(0);
    std::complex<double> b = getValue(1);
    std::complex<double> c = getValue(2);
    std::complex<double> d = getValue(3);     
    if(c != 0.0){
        eigenVector.setValue(lambda - d, 0);
        eigenVector.setValue(c, 1);
    }
    else if(b != 0.0){
        eigenVector.setValue(b, 0);
        eigenVector.setValue(lambda - a, 1);
    }
    else{
        eigenVector.setValue(1.0 - i, 0);
        eigenVector.setValue((double)i, 1);
    }
    return eigenVector.normalize();
}

double HermitianOperator::expectation(Qbit q){
    return (q.bra() * (*this) * q.ket()).getValue(0).real();
}

HermitianOperator HermitianOperator::I(){
    ComplexMatrix mat = Qbit::zero().ket()*Qbit::zero().bra() + 
                        Qbit::one().ket()*Qbit::one().bra();
    return HermitianOperator(mat);
}

HermitianOperator HermitianOperator::X(){
    ComplexMatrix mat = Qbit::zero().ket()*Qbit::one().bra() + 
                        Qbit::one().ket()*Qbit::zero().bra();
    return HermitianOperator(mat);
}

HermitianOperator HermitianOperator::Z(){
    ComplexMatrix mat = Qbit::plus().ket()*Qbit::minus().bra() + 
                        Qbit::minus().ket()*Qbit::plus().bra();
    return HermitianOperator(mat);
}

HermitianOperator HermitianOperator::Y(){
    ComplexMatrix mat = std::complex<double>(0,1) * X() * Z();
    return HermitianOperator(mat);
}

HermitianOperator HermitianOperator::H(){
    ComplexMatrix mat = Qbit::plus().ket()*Qbit::zero().bra() + 
                        Qbit::minus().ket()*Qbit::one().bra();
    return HermitianOperator(mat);
}

HermitianOperator HermitianOperator::PI(unsigned i){
    if(std::abs((int)i) > 1){
        std::cout << "ERROR: Index out off projector bounds!" << std::endl;
        exit(0);
    }

    ComplexMatrix mat = Qbit(1-i,i).ket()*Qbit(1-i,i).bra();
    return HermitianOperator(mat);
}