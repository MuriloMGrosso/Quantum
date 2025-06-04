#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../includes/qbit.h"

int main(){
    std::srand(std::time(0));

    Qbit q1 = Qbit::plus();
    Qbit q2;

    q1.print();
    q2.print();

    std::cout << Qbit::braket(q1, q1) << std::endl;

    return 0;
}
