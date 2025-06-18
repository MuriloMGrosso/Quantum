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
    Qbit q;
public:
    Player(int x, Qbit q);
    int oneStrategy();
    int zeroStrategy();
    int copyStrategy();
    int randomStrategy();
    int oppositStrategy();
    int quantumStrategy();
};

#endif