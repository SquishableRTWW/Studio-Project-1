#include "thornhull.h"
using namespace std;

thornhull::thornhull(void)
{
	element = "nature";
	setLevel();
	setKills();
	setOGStats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
	}
	for (int i = 0; i < 2; i++)
	{
		setMove(i);
	}
}
void thornhull::levelUp(void)
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
void thornhull::setMove(int i)
{
	string fireMoveList[4] = { "flamethrower", "fire-up", "heatwave", "blast burn" };
	moves.setMoveWithName(fireMoveList[i], i);
}
thornhull::~thornhull(void)
{

}
