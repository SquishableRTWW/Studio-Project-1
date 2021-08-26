#include "moveList.h"
#include "monster.h"
#include <iostream>
#include <string>

moveList::moveList(void)
{
	for (int i = 0; i < 4; i++)
	{
		moves[i] = "None";
	}
	damage[0] = 5; damage[1] = 0; damage[2] = 10; damage[3] = 25;
}
void moveList::setMoveWithName(string move,int position)
{
	moves[position] = move;
}
string moveList::getMove(int i)
{
	return moves[i];
}
int moveList::getMoveDamage(int i)
{
	return damage[i];
}
moveList::~moveList(void)
{

}
