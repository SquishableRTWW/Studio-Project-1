#include "azure.h"
using namespace std;

azure::azure(void)
{
	element = "water";
	setName("azure");
	setLevel();
	setKills();
	setOGStats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(3); setAttack(1); setDefence(1); setSpeed(1);
	}
	for (int i = 0; i < 2; i++)
	{
		setMove(i);
	}
}
void azure::levelUp(void)
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
void azure::setMove(int i)
{
	string waterMoveList[4] = { "bubble beam", "drought", "thrash", "riptide" };
	moves.setMoveWithName(waterMoveList[i], i);
}
azure::~azure(void)
{

}
