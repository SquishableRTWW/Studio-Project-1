#include "oris.h"
using namespace std;

oris::oris(void)
{
	element = "earth";
	setName("oris");
	setLevel();
	setKills();
	setOGStats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(1); setDefence(2); setSpeed(1);
	}
	for (int i = 0; i < 2; i++)
	{
		setMove(i);
	}
}
void oris::levelUp(void)
{
	upKill();
	if (getKills() % 3 == 0)
	{
		upLevel();
		setHealth(2); setAttack(1); setDefence(2); setSpeed(1);
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
void oris::setMove(int i)
{
	string earthMoveList[4] = { "rock throw", "bulk up", "landslide", "earthquake"};
	moves.setMoveWithName(earthMoveList[i], i);
}
oris::~oris(void)
{

}