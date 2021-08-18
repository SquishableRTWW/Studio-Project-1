#include "monster.h"
#include <iostream>
#include <string>
#include <random>

monster::monster(void)
{
	element = "NULL";
	level = (rand() % 4) + 2;
	health = 10;
	attack = 5;
	defence = 3;
	speed = 10;
	kills = 0;
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
monster::~monster(void)
{

}
