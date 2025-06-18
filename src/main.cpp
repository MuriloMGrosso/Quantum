#include <iostream>
#include <complex>
#include <cstdlib>
#include <ctime>
#include "../includes/complexMatrix.h"
#include "../includes/quantum.h"
#include "../includes/chsh.h"

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

    Qbit qA = Q_ZERO;
    Qbit qB = Q_ZERO;

    std::cout << ComplexMatrix::tensorProduct(qA.ket(), qB.ket()) << std::endl;

    H.apply(qA);

    std::cout << ComplexMatrix::tensorProduct(qA.ket(), qB.ket()) << std::endl;

    X.apply(qB);

    std::cout << ComplexMatrix::tensorProduct(qA.ket(), qB.ket()) << std::endl;

    // Qbit qA, qB;
    // int x, y, a, b;
    // double n = 10000;
    // double winCount = 0;

    // for(int i = 0; i < n; i++){
    //     Qbit::entangle(qA, qB);

    //     Referee referee(x,y);
    //     Player alice(x,qA);
    //     Player bob(y,qB);

    //     a = alice.quantumStrategy();
    //     b = bob.quantumStrategy();
    //     winCount += referee.check(a,b);
    // }

    // std::cout << "Win rate: " << winCount/n*100 << "%" << std::endl;

    return 0;
}