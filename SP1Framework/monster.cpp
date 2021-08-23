#include "monster.h"
#include "oris.h"
#include "lavarous.h"
#include "azure.h"
#include "thornhull.h"
#include <iostream>
#include <string>
#include <random>

monster::monster(void)
{
	element = "NULL";
	name = "NULL";
	level = (rand() % 4) + 2;
	health = 10;
	attack = 5;
	defence = 3;
	speed = 10;
	kills = 0;
}
void monster::setName(string name)
{
	this->name = name;
}
void monster::setOGStats(void)
{
	this->health = 10;
	this->attack = 6;
	this->defence = 3;
	this->speed = 10;
}
void monster::setOGBossStats(void)
{
	this->health = 20;
	this->attack = 14;
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
void monster::upKill(void)
{
	kills++;
}
void monster::upLevel(void)
{
	level++;
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
string monster::getElement(void)
{
	return element;
}
monster::~monster(void)
{

}
