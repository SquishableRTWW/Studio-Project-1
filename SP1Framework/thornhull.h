#pragma once
#include "monster.h"
class thornhull : public monster
{
private:
	string element;
	moveList moves;
public:
	thornhull(void); //Default constructor
	void levelUp();
	void setMove(int i);
	~thornhull(void);
};

