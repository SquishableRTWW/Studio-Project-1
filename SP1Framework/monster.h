#pragma once
#include "moveList.h"
#include <string>
class monster
{
private:
	moveList move;
	string element;
	string name;
	int level;
	int health;
	int attack;
	int defence;
	int speed;
	int kills;
public:
	monster(void);
	void setName(string name);
	void setOGStats(void);
	void setOGBossStats(void);
	void setOGBoss2Stats(void);
	void setHealth(int i);
	void setAttack(int i);
	void setDefence(int i);
	void setSpeed(int i);
	void setLevel(void);
	void setKills(void);
	void upKill(void);
	void upLevel(void);
	string getName(void);
	int getHealth(void);
	int getAttack(void);
	int getDefence(void);
	int getSpeed(void);
	int getKills(void);
	int getLevel(void);
	string getElement(void);
	~monster(void);
};

