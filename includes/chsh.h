/*----------------------------------------------------------------------------------------------------------------------------
   _____ _    _  _____ _    _                                                       |
  / ____| |  | |/ ____| |  | |                                                      | CHSH:
 | |    | |__| | (___ | |__| |   __ _  __ _ _ __ ___   ___                          | A simple implementation of the CHSH
 | |    |  __  |\___ \|  __  |  / _` |/ _` | '_ ` _ \ / _ \                         | game and some basic strategies.
 | |____| |  | |____) | |  | | | (_| | (_| | | | | | |  __/                         |
  \_____|_|  |_|_____/|_|  |_|  \__, |\__,_|_| |_| |_|\___|                         |
                                 __/ |                                              | By Murilo M. Grosso
                                |___/                                               |
----------------------------------------------------------------------------------------------------------------------------*/

#ifndef CHSH_H
#define CHSH_H

#include "../includes/quantum.h"

/*--------------------------------------------------------------------------------------------------------------------------*/

class Referee{
private:
    int x, y;                                                                       // Referee bits
public:
    Referee(int &x, int &y);                                                        // Referee constructor
    int check(int a, int b);                                                        // Checks whether they won (1) or lost (0)    
};

class Player{
private:
    int x;                                                                          // Player bit
    Qbit* q;                                                                        // Player qbit (if using)
public:
    Player(int x);                                                                  // Player constructor (no qbit)
    Player(int x, Qbit &q);                                                         // Player constructor (with qbit)
    int copyStrategy();                                                             // Returns same as referee
    int randomStrategy();                                                           // Returns random bit
    int oppositeStrategy();                                                         // Returns oposite of referee
    int constStrategy(int n);                                                       // Returns always the same value
    int quantumStrategy(double theta0, double theta1);                              // Returns measurement of qbit
};

#endif