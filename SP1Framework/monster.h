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
	void setLevel(int i);
	void setKills(void);
	void setElement(string element);
	void setMove(monster& monster, int i);
	void upKill(void);
	void upLevel(void);
	void setWildMonster(monster& monster, int i);
	void levelUp(monster& monster);
	string getName(void);
	int getHealth(void);
	int getAttack(void);
	int getDefence(void);
	int getSpeed(void);
	int getKills(void);
	int getLevel(void);
	int getMaxHealth(void);
	int getMoveDamage(int i);
	string getMove(int i);
	string getElement(void);
	~monster(void);
};

