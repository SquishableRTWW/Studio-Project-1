#include "ignis.h"
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
	for (int i = 0; i < 2; i++)
	{
		setMove(i);
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
	if (getLevel() == 8)
	{
		setMove(2);
	}
}
void ignis::setMove(int i)
{
	string fireMoveList[4] = { "flamethrower", "enrage", "scorch", "blast burn" };
	moves.setMoveWithName(fireMoveList[i], i);
}
ignis::~ignis(void)
{

}
