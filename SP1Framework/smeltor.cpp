#include "smeltor.h"
using namespace std;

smeltor::smeltor(void)
{
	element = "earth";
	setName("smeltor");
	setOGBoss2Stats();
	for (int i = 0; i < getLevel(); i++)
	{
		setHealth(2); setAttack(1); setDefence(2); setSpeed(1);
	}
	for (int i = 0; i < 4; i++)
	{
		setMove(i);
	}
}
void smeltor::setMove(int i)
{
	string boss2MoveList[4] = { "rock tomb", "rupture", "lava spout", "drill drive" };
	moves.setMoveWithName(boss2MoveList[i], i);
}
smeltor::~smeltor(void)
{

}
