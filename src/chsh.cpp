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
    return (x&y) == (a^b) ? 1 : 0;
}

Player::Player(int x) : x(x), q(0){}
Player::Player(int x, Qbit &q) : x(x), q(&q){}

int Player::constStrategy(int n)    { return n; }
int Player::copyStrategy()          { return x; }
int Player::oppositeStrategy()       { return !x; }

int Player::randomStrategy(){ 
    return (double)std::rand() / RAND_MAX > 0.5 ? 1 : 0; 
}

int Player::quantumStrategy(double theta0, double theta1){
    if(!q){
        std::cout << "ERROR: Missing Qbit for quantum strategy!" << std::endl;
        exit(0);
    }
    UnitaryOperator::Ry(theta0*(1-x) + theta1*x).apply(*q);
    return UnitaryOperator::Z().measure(*q) > 0 ? 1 : 0;
}