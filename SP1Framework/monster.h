#pragma once
#include "moveList.h"
#include <string>
class monster
{
private:
	moveList move;
	string element;
	int level;
	int health;
	int attack;
	int defence;
	int speed;
	int kills;
public:
	monster(void);
	void setOGStats(void);
	void setOGBossStats(void);
	void setHealth(int i);
	void setAttack(int i);
	void setDefence(int i);
	void setSpeed(int i);
	void setLevel();
	void setKills();
	void upKill();
	void upLevel();
	int getHealth(void);
	int getAttack(void);
	int getDefence(void);
	int getSpeed(void);
	int getKills(void);
	int getLevel(void);
	string getElement(void);
	~monster(void);
};

