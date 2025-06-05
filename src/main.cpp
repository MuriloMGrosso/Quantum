#include <iostream>
#include <complex>
#include <cstdlib>
#include <ctime>
#include "../includes/complexMatrix.h"
#include "../includes/quantum.h"

int main(){
    std::srand(std::time(0));

    Qbit qZero  = Qbit::zero();
    Qbit qOne   = Qbit::one();
    Qbit qPlus  = Qbit::plus();
    Qbit qMinus = Qbit::minus();
    Qbit q;

    ComplexMatrix I = qPlus.ket()*qPlus.bra() + qMinus.ket()*qMinus.bra();

    ComplexMatrix X = ComplexMatrix(2,2);
    X.setValue(0,0);
    X.setValue(1,1);
    X.setValue(1,2);
    X.setValue(0,3);

    ComplexMatrix Z = ComplexMatrix(2,2);
    Z.setValue(1,0);
    Z.setValue(0,1);
    Z.setValue(0,2);
    Z.setValue(-1,3);

    ComplexMatrix Y = std::complex<double>(0,1) * X * Z;

    ComplexMatrix H = qPlus.ket()*qZero.bra() + qMinus.ket()*qOne.bra();

    std::cout << "Zero ket:" << std::endl;
    std::cout << qZero.ket() << std::endl;
    std::cout << "Zero bra:" << std::endl;
    std::cout << qZero.bra() << std::endl;
    std::cout << "One ket:" << std::endl;
    std::cout << qOne.ket() << std::endl;
    std::cout << "Plus ket:" << std::endl;
    std::cout << qPlus.ket() << std::endl;
    std::cout << "Minus ket:" << std::endl;
    std::cout << qMinus.ket() << std::endl;
    std::cout << "Identity:" << std::endl;
    std::cout << I << std::endl;
    std::cout << "Not operator:" << std::endl;
    std::cout << X << std::endl;
    std::cout << "Phase-flip operator:" << std::endl;
    std::cout << Z << std::endl;
    std::cout << "Y operator:" << std::endl;
    std::cout << Y << std::endl;
    std::cout << "Hadamard gate:" << std::endl;
    std::cout << H << std::endl;

    ComplexMatrix V = H * qOne.ket();

    std::cout << "Result:" << std::endl;
    std::cout << V << std::endl;

    return 0;
}
