#pragma once
#include "monster.h"
#include <string>
using namespace std;
class ignis : public monster
{
private:
	string element;

public:
	ignis(void); //Default constructor
	void levelUp();
};

