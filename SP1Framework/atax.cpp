#include "atax.h"
using namespace std;

atax::atax(void)
{
	element = "water";
	setName("atax");
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
	string boss1MoveList[4] = { "aqua tail", "scald", "water spout", "flash flood" };
	moves.setMoveWithName(boss1MoveList[i], i);
}
atax::~atax(void)
{

}
