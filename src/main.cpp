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
#define I UnitaryOperator::I()
#define X UnitaryOperator::X()
#define Z UnitaryOperator::Z()
#define Y UnitaryOperator::Y()
#define H UnitaryOperator::H()
#define CNOT UnitaryOperator::CNOT()

#define PI 3.14159265359 

int main(){
    std::srand(std::time(0));

    Qbit qA, qB;
    int x, y, a, b;
    double n = 10000;
    double winCount = 0;

    for(int i = 0; i < n; i++){
        Referee referee(x,y);

        qA = Q_ZERO;
        qB = Q_ZERO;
        CompositeSystem compositeSystem(qA, qB);
        
        H.apply(qA);
        compositeSystem.applyCNOT();

        UnitaryOperator::Ry(PI/2 * x).apply(qA);
        UnitaryOperator::Ry(-PI/4 * (y * 2 - 1)).apply(qB);
        a = Z.measure(qA) > 0 ? 0 : 1;
        b = Z.measure(qB) > 0 ? 0 : 1;

        winCount += referee.check(a,b);
    }

    std::cout << "Win rate: " << winCount/n*100 << "%" << std::endl;

    return 0;
}