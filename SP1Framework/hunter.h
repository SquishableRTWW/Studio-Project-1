#pragma once
#include <string>
#include "monster.h"
#include "ignis.h"
#include "typhis.h"
#include "vitalus.h"
#include "oris.h"

class hunter
{
private:
	string name;
	monster party[6];
public:
	hunter(void);
	void setname(string n);
	string getname();
	void choosestarter(int s);
	void addparty(int m);
	~hunter(void);
};