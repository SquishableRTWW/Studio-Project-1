#pragma once
#include "monster.h"
#include "moveList.h"
#include <string>
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
};

