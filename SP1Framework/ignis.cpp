#include "ignis.h"
#include "moveList.h"
#include "monster.h"
using namespace std;

ignis::ignis(void)
{
	element = "fire";
	setLevel();
	setKills();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
	}
}
void ignis::levelUp(void)
{
	upKill();
	if (getKills() % 3 == 0)
	{
		upLevel();
		setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
	}
}
