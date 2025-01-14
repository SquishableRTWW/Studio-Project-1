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
	int direction, range;
	bool check;
public:
	hunter(void);
	void setname(string n);
	string getname(void);
	void choosestarter(int s);
	void addparty(monster& monster);
	void setDirRange(int d, int r);
	void setcheck(bool c);
	bool getcheck(void);
	int getdirection(void);
	int getrange(void);
	monster getMonster(int m);
	//get functions for monsters in party
	string getMname(int i);
	int getMlvl(int i);
	int getMhealth(int i);
	int getMattack(int i);
	int getMdefense(int i);
	int getMspeed(int i);
	void setMHealth(int i, int  j);
	void setMAttack(int i, int  j);
	void setMDefence(int i, int  j);
	void setMSpeed(int i, int  j);
	string getMelement(int i);
	int getMkills(int i);
	~hunter(void);
};