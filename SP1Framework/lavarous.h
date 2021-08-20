#pragma once
#include "monster.h"
class lavarous : public monster
{
private:
	string element;
	moveList moves;
public:
	lavarous(void); //Default constructor
	void levelUp();
	void setMove(int i);
	~lavarous(void);
};

