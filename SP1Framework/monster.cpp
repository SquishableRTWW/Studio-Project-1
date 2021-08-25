#include "monster.h"
#include "oris.h"
#include "lavarous.h"
#include "azure.h"
#include "thornhull.h"
#include "ignis.h"
#include <iostream>
#include <string>
#include <random>

monster::monster(void)
{
	element = "NULL";
	name = "NULL";
	level = (rand() % 4) + 2;
	health = 0;
	attack = 0;
	defence = 0;
	speed = 0;
	kills = 0;
}
void monster::setName(string name)
{
	this->name = name;
}
void monster::setOGStats(void)
{
	this->health = 30;
	this->attack = 6;
	this->defence = 3;
	this->speed = 10;
	this->kills = 0;
}
void monster::setOGBossStats(void)
{
	this->health = 50;
	this->attack = 8;
	this->defence = 9;
	this->speed = 14;
	this->level = 14;
}
void monster::setOGBoss2Stats(void)
{
	this->health = 27;
	this->attack = 10;
	this->defence = 12;
	this->speed = 8;
	this->level = 25;
}
void monster::setHealth(int i)
{
	this->health += i;
}
void monster::setAttack(int i)
{
	this->attack += i;
}
void monster::setDefence(int i)
{
	this->defence += i;
}
void monster::setSpeed(int i)
{
	this->speed += i;
}
void monster::setLevel()
{
	this->level = (rand() % 4) + 2;
}
void monster::setLevel(int i)
{
	this->level = i;
}
void monster::setKills()
{
	this->kills = 0;
}
void monster::setElement(string element)
{
	this->element = element;
}
void monster::setMove(monster& monster, int i)
{
	string fireMoveList[4] = { "flamethrower", "enrage", "scorch", "blast burn" };
	string natureMoveList[4] = { "leaf blade", "entangle", "power whip", "frenzy plant" };
	string waterMoveList[4] = { "water gun", "drown", "waterfall", "hydro pump" };
	string boss1MoveList[4] = { "aqua tail", "scald", "water spout", "flash flood" };
	string waterMoveList2[4] = { "bubble beam", "drought", "thrash", "riptide" };
	string earthMoveList[4] = { "rock throw", "bulk up", "landslide", "earthquake" };
	string boss2MoveList[4] = { "rock tomb", "rupture", "lava spout", "drill drive" };
	string fireMoveList2[4] = { "flamethrower", "fire-up", "heatwave", "blast burn" };
	if (monster.getName() == "ignis")
	{
		move.setMoveWithName(fireMoveList[i], i);
	}
	if (monster.getName() == "typhis")
	{
		move.setMoveWithName(waterMoveList[i], i);
	}
	if (monster.getName() == "vitalus")
	{
		move.setMoveWithName(natureMoveList[i], i);
	}
	if (monster.getName() == "oris")
	{
		move.setMoveWithName(earthMoveList[i], i);
	}
	if (monster.getName() == "azure")
	{
		move.setMoveWithName(waterMoveList2[i], i);
	}
	if (monster.getName() == "lavarous")
	{
		move.setMoveWithName(fireMoveList2[i], i);
	}
	if (monster.getName() == "thornhull")
	{
		move.setMoveWithName(natureMoveList[i], i);
	}
	if (monster.getName() == "atax")
	{
		move.setMoveWithName(boss1MoveList[i], i);
	}
	if (monster.getName() == "smeltor")
	{
		move.setMoveWithName(boss2MoveList[i], i);
	}

}
void monster::upKill(void)
{
	kills += 1;
}
void monster::upLevel(void)
{
	level += 1;
}
void monster::setWildMonster(monster& monster, int i)
{
	switch (i)
	{
	case 1:
		monster = oris();
		break;
	case 2:
		monster = thornhull();
		break;
	case 3:
		monster = azure();
		break;
	case 4:
		monster = lavarous();
		break;
	}
}
void monster::levelUp(monster& monster)
{
	if (monster.getName() == "ignis")
	{
		kills++;
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "typhis")
	{
		kills++;
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(3); setAttack(1); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "vitalus")
	{
		kills;
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "azure")
	{
		upKill();
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "lavarous")
	{
		upKill();
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "thornhull")
	{
		upKill();
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
	if (monster.getName() == "oris")
	{
		upKill();
		if (getKills() % 3 == 0)
		{
			upLevel();
			setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
		}
		if (getLevel() == 8)
		{
			setMove(monster, 2);
		}
		if (getLevel() == 14)
		{
			setMove(monster, 3);
		}
	}
}
string monster::getName(void)
{
	return name;
}
int monster::getHealth(void)
{
	return health;
}
int monster::getAttack(void)
{
	return attack;
}
int monster::getDefence(void)
{
	return defence;
}
int monster::getSpeed(void)
{
	return speed;
}
int monster::getKills(void)
{
	return kills;
}
int monster::getLevel(void)
{
	return level;
}
string monster::getMove(int i)
{
	return move.getMove(i);
}
string monster::getElement(void)
{
	return element;
}
int monster::getMaxHealth(void)
{
	if (getElement() == "water")
	{
		return (30 + (3 * getLevel()));
	}
	else
	{
		return (30 + (2 * getLevel()));
	}
}
int monster::getMoveDamage(int i)
{
	return move.getMoveDamage(i);
}
monster::~monster(void)
{

}
