#pragma once
#include "monster.h"
class oris :
    public monster
{
private:
    string element;
    moveList moves;
public:
    oris(void); //Default constructor
    void levelUp(void);
    void setMove(int i);
    ~oris(void);


};

