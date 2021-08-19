#include "typhis.h"
using namespace std;

typhis::typhis(void)
{
	element = "water";
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
void typhis::levelUp(void)
{
	upKill();
	if (getKills() % 3 == 0)
	{
		upLevel();
		setHealth(3); setAttack(1); setDefence(1); setSpeed(1);
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
void typhis::setMove(int i)
{
	string waterMoveList[4] = {"water gun", "drown", "waterfall", "hydro pump"};
	moves.setMoveWithName(waterMoveList[i], i);
}
typhis::~typhis(void)
{

}