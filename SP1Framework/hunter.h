#pragma once
#include <string>
#include "monster.h"
#include "ignis.h"
#include "typhis.h"
#include "vitalus.h"
#include "oris.h"
#include "lavarous.h"
#include "azure.h"
#include "Entity.h"


class hunter: public Entity
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
	monster getMonster(int m);
	//get functions for monsters in party
	string getMname(int i);
	int getMlvl(int i);
	int getMhealth(int i);
	int getMattack(int i);
	int getMdefense(int i);
	int getMspeed(int i);
	string getMelement(int i);
	int getMkills(int i);
	~hunter(void);
};