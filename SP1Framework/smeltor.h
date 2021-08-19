#pragma once
#include "monster.h"
class smeltor : public monster
{
private:
	string element;
	moveList moves;
public:
	smeltor(void);
	void setMove(int i);
	~smeltor(void);
};

