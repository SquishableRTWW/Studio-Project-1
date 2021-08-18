#pragma once
#include "moveList.h"
#include <string>
class monster
{
private:
	moveList move;
	int level;
	int health;
	int attack;
	int defence;
	int speed;
	int kills;
public:
	monster(void);
	void setHealth(int i);
	void setAttack(int i);
	void setDefence(int i);
	void setSpeed(int i);
	void upKill();
	void upLevel();
	int getHealth(void);
	int getAttack(void);
	int getDefence(void);
	int getSpeed(void);
	int getKills(void);
	int getLevel(void);
};

