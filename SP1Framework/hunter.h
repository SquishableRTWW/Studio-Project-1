#pragma once
#include <string>
#include "monster.h"

class hunter
{
private:
	string name;
	monster party[6];
public:
	hunter(void);
	void setname(string n);
	string getname();
};