#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../includes/qbit.h"
#include "../includes/matrix.h"

int main(){
    std::srand(std::time(0));

    Qbit qZero  = Qbit::zero();
    Qbit qOne   = Qbit::one();
    Qbit qPlus  = Qbit::plus();
    Qbit qMinus = Qbit::minus();
    Qbit q;

    std::cout << Qbit::braket(qZero, qZero) << std::endl;
    std::cout << Qbit::braket(qZero, qOne) << std::endl;
    std::cout << Qbit::braket(qOne, qZero) << std::endl;
    std::cout << Qbit::braket(qPlus, qMinus) << std::endl;
    std::cout << Qbit::braket(qZero, qPlus) << std::endl;
    std::cout << Qbit::braket(qOne, qMinus) << std::endl;
    std::cout << Qbit::braket(qZero, q) << std::endl;
    std::cout << Qbit::braket(qOne, q) << std::endl;

    return 0;
}
