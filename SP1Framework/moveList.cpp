#include "moveList.h"
#include <iostream>
#include <string>

moveList::moveList(void)
{
	for (int i = 0; i < 4; i++)
	{
		moves[i] = "None";
	}
}

moveList::moveList(string element)
{
	for (int i = 0; i < 4; i++)
	{
		moves[i] = "None";
	}
	if (element == "fire")
	{
		string fireMoveList[4] = { "flamethrower", "enrage", "scorch", "blast burn" };
		for (int i = 0; i < 4; i++)
		{
			moves[i] = fireMoveList[i];
		}
	}
	if (element == "water")
	{
		string waterMoveList[4] = { "water gun", "drown", "waterfall", "hydro pump" };
		for (int i = 0; i < 4; i++)
		{
			moves[i] = waterMoveList[i];
		}
	}
	if (element == "earth")
	{
		string earthMoveList[4] = { "rock throw", "bulk up", "landslide", "earthquake" };
		for (int i = 0; i < 4; i++)
		{
			moves[i] = earthMoveList[i];
		}
	}
	if (element == "nature")
	{
		string natureMoveList[4] = { "leaf blade", "entangle", "power whip", "frenzy plant" };
		for (int i = 0; i < 4; i++)
		{
			moves[i] = natureMoveList[i];
		}
	}
}
