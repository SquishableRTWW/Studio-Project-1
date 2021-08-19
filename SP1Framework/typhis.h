#pragma once
#include "monster.h"
class typhis : public monster
{
private:
	string element;
	moveList moves;
public:
	typhis(void); //Default constructor
	void levelUp(void);
	void setMove(int i);
	~typhis(void);
};

