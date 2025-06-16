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

    HermitianOperator I = HermitianOperator::I();
    HermitianOperator X = HermitianOperator::X();
    HermitianOperator Z = HermitianOperator::Z();
    HermitianOperator Y = HermitianOperator::Y();
    HermitianOperator H = HermitianOperator::H();
    HermitianOperator PI0 = HermitianOperator::PI(0);
    HermitianOperator PI1 = HermitianOperator::PI(1);

    std::cout << X.getEigenValue(1) << std::endl;
    std::cout << X.getEigenVector(1) << std::endl;

    std::cout << q.ket() << std::endl;

    for(int i = 0; i < 2; i++)
        std::cout << X.measure(q) << std::endl;
    for(int i = 0; i < 2; i++)
        std::cout << Z.measure(q) << std::endl;
    for(int i = 0; i < 2; i++)
        std::cout << X.measure(q) << std::endl;

    std::cout << q.ket() << std::endl;

    return 0;
}
