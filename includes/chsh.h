#ifndef CHSH_H
#define CHSH_H

#include "../includes/quantum.h"

class Referee{
private:
    int x, y;
public:
    Referee(int &x, int &y);
    int check(int a, int b);
};

class Player{
private:
    int x;
    Qbit* q;
public:
    Player(int x);
    Player(int x, Qbit &q);
    int copyStrategy();
    int randomStrategy();
    int oppositeStrategy();
    int constStrategy(int n);
    int quantumStrategy(double theta0, double theta1);
};

#endif