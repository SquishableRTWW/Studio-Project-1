#include "vitalus.h"
using namespace std;

vitalus::vitalus(void)
{
	element = "nature";
	setName("vitalus");
	setLevel(5);
	setKills();
	setOGStats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(1); setDefence(1); setSpeed(2);
	}
	for (int i = 0; i < 2; i++)
	{
		setMove(i);
	}
}
void vitalus::levelUp(void)
{
	upKill();
	if (getKills() % 3 == 0)
	{
		upLevel();
		setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
	}
	if (getLevel() == 8)
	{
		setMove(2);
	}
	if (getLevel() == 14)
	{
		setMove(3);
	}
}
void vitalus::setMove(int i)
{
	string natureMoveList[4] = { "leaf blade", "entangle", "power whip", "frenzy plant"};
	moves.setMoveWithName(natureMoveList[i], i);
}
vitalus::~vitalus(void)
{

}
