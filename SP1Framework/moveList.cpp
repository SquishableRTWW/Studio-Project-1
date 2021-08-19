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
	string waterMoveList[4] = { "water gun", "drown", "waterfall", "hydro pump" };
	string earthMoveList[4] = { "rock throw", "bulk up", "landslide", "earthquake" };
	string natureMoveList[4] = { "leaf blade", "entangle", "power whip", "frenzy plant" };
}
void moveList::setMoveWithName(string move,int position)
{
	moves[position] = move;
}
string moveList::getMove(int i)
{
	return moves[i];
}
moveList::~moveList(void)
{

}
