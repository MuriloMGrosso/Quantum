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
#define BAR_LEN 50
#define N_STRATEGIES 6

int main(){
    std::srand(std::time(0));

    Qbit qA, qB;
    int x, y, a, b, n;
    double temp;
    double winCount[N_STRATEGIES];

    std::cout << "1) Random Strategy " << std::endl;
    std::cout << "2) Copy Strategy " << std::endl;
    std::cout << "3) Opposite Strategy " << std::endl;
    std::cout << "4) Always zero Strategy " << std::endl;
    std::cout << "5) Always one Strategy " << std::endl;
    std::cout << "6) Quantum Strategy " << std::endl;
    std::cout << std::endl;

    while(true){
        n++;

        qA = Q_ZERO;
        qB = Q_ZERO;
        CompositeSystem compositeSystem(qA, qB);
        H.apply(qA);
        compositeSystem.applyCNOT();

        Referee referee(x,y);
        Player alice(x,qA);
        Player bob(y,qB);

        a = alice.randomStrategy();
        b = bob.randomStrategy();
        winCount[0] += referee.check(a,b);

        a = alice.copyStrategy();
        b = bob.copyStrategy();
        winCount[1] += referee.check(a,b);

        a = alice.oppositeStrategy();
        b = bob.oppositeStrategy();
        winCount[2] += referee.check(a,b);

        a = alice.constStrategy(0);
        b = bob.constStrategy(0);
        winCount[3] += referee.check(a,b);

        a = alice.constStrategy(1);
        b = bob.constStrategy(1);
        winCount[4] += referee.check(a,b);

        a = alice.quantumStrategy(0, PI/2);
        b = bob.quantumStrategy(PI/4, -PI/4);
        winCount[5] += referee.check(a,b);

        if(n % 1000 != 0)
            continue;

        std::cout << "WIN RATE (" << n << " games played)";
        for(int i = 0; i < N_STRATEGIES; i++){
            temp = winCount[i]/n;
            std::cout << std::endl << i+1 << ") [";
            for(int k = 0; k < std::ceil(BAR_LEN * temp); k++)
                std::cout << "#";
            for(int k = 0; k < std::floor(BAR_LEN * (1-temp)); k++)
                std::cout << ".";
            std::cout << "] " << temp*100 << "%";
        }

        std::cout << "\033[" << N_STRATEGIES << "F";
    }

    return 0;
}