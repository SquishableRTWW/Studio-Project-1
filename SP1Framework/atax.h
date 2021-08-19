#pragma once
#include "monster.h"
class atax : public monster
{
private:
	string element;
	moveList moves;
public:
	atax(void); //Default constructor.
	~atax(void);
};

