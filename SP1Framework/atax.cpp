#include "atax.h"
using namespace std;

atax::atax(void)
{
	element = "NULL";
	setOGBossStats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(2); setDefence(1); setSpeed(1);
	}
	for (int i = 0; i < 4; i++)
	{
		setMove(i);
	}

}
void atax::setMove(int i)
{
	string boss1MoveList[4] = { "shadow ball", "engulf", "jumpscare", "dark void" };
	moves.setMoveWithName(boss1MoveList[i], i);
}
atax::~atax(void)
{

}
