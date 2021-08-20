#pragma once
#include "monster.h"
class azure : public monster
{
private:
	string element;
	moveList moves;
public:
	azure(void); //Default constructor
	void levelUp();
	void setMove(int i);
	~azure(void);

};

