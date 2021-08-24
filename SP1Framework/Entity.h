#pragma once
#include "Framework/console.h"
class Entity
{
private:
	COORD pos;
	enum Entities//enumeration to store the types of entities
	{
		E_Hunter,
		E_NPC,
		E_Boss
	};
public:
	Entity(void);
	void setposition(int X, int Y);
	COORD getposition();
	int getX();
	int getY();
};

