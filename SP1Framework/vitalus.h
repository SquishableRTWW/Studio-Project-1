#pragma once
#include "monster.h"
class vitalus : public monster
{
private:
	string element;
	moveList moves;
public:
	vitalus(void); //Default constructor
	void levelUp(void);
	void setMove(int i);
	~vitalus(void);
};

