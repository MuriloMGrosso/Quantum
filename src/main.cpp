#include <iostream>
#include <complex>
#include <cstdlib>
#include <ctime>
#include "../includes/complexMatrix.h"
#include "../includes/quantum.h"

#define Q_ZERO Qbit::zero()
#define Q_ONE Qbit::one()
#define Q_PLUS Qbit::plus()
#define Q_MINUS Qbit::minus()
#define I HermitianOperator::I()
#define X HermitianOperator::X()
#define Z HermitianOperator::Z()
#define Y HermitianOperator::Y()
#define H HermitianOperator::H()
#define PI0 HermitianOperator::PI0(0)
#define PI1 HermitianOperator::PI1(1)

int main(){
    std::srand(std::time(0));

    Qbit qA, qB;
    Qdit::entangle(qA, qB);

    std::cout << "Measure entangled particles in Z" << std::endl;
    std::cout << Z.measure(qA) << std::endl;
    std::cout << Z.measure(qB) << std::endl;

    std::cout << "Measure A in Z" << std::endl;
    std::cout << Z.measure(qA) << std::endl;
    std::cout << Z.measure(qA) << std::endl;
    std::cout << Z.measure(qA) << std::endl;

    std::cout << "Measure A in X" << std::endl;
    std::cout << X.measure(qA) << std::endl;

    std::cout << "Particles in Z" << std::endl;
    std::cout << Z.measure(qA) << std::endl;
    std::cout << Z.measure(qB) << std::endl;

    return 0;
}
