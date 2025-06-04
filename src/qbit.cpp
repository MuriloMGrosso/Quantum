#include "../includes/qbit.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

Qbit::Qbit(){
    alpha = (double)std::rand() / RAND_MAX * 2 - 1;
    beta = std::sqrt(1 - alpha*alpha);
    beta *= (double)std::rand() / RAND_MAX > 0.5 ? 1 : -1;
}

Qbit::Qbit(double alpha, double beta) : alpha(alpha), beta(beta) {
    if(abs(alpha*alpha + beta*beta - 1) > 0.0000000000001){
        std::cout << "Invalid qbit amplitudes!" << std::endl;
        exit(0);
    }
}

double Qbit::getAlpha(){
    return alpha;
}

double Qbit::getBeta(){
    return beta;
}

void Qbit::print(){
    std::cout << "[" << alpha << ", " << beta << "]" << std::endl;
}

Qbit Qbit::zero()   { return Qbit(1,0); }
Qbit Qbit::one()    { return Qbit(0,1); }
Qbit Qbit::plus()   { return Qbit(1/std::sqrt(2),1/std::sqrt(2)); }
Qbit Qbit::minus()  { return Qbit(1/std::sqrt(2),-1/std::sqrt(2)); }

double Qbit::braket(Qbit q1, Qbit q2){
    return q1.getAlpha()*q2.getAlpha() + q1.getBeta()*q2.getBeta();
}