#pragma once
#include "monster.h"
using namespace std;
class ignis : public monster
{
private:
	string element;
	moveList moves;
public:
	ignis(void); //Default constructor
	void levelUp();
	void setMove(int i);
	~ignis(void);
};

