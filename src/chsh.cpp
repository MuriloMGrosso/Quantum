#include "../includes/chsh.h"
#include <iostream>
#include <cstdlib>

Referee::Referee(int &x, int &y){
    x = (double)std::rand() / RAND_MAX > 0.5 ? 1 : 0;
    y = (double)std::rand() / RAND_MAX > 0.5 ? 1 : 0;
    this->x = x;
    this->y = y;
}

int Referee::check(int a, int b){
    return x*y == a^b ? 1 : 0;
}

Player::Player(int x, Qbit q) : x(x), q(q){}

int Player::oneStrategy(){ return 1; }
int Player::zeroStrategy(){ return 0; }
int Player::copyStrategy(){ return x; }
int Player::randomStrategy(){ return (double)std::rand() / RAND_MAX > 0.5 ? 1 : 0; }
int Player::oppositStrategy(){ return !x; }

int Player::quantumStrategy(){
    if(x == 0)
        return (UnitaryOperator::Z().measure(q) + 1)/2;
    return (UnitaryOperator::Z().measure(q) + 1)/2;
}