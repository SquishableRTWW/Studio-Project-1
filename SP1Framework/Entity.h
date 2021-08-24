#pragma once
#include "Framework/console.h"
class Entity
{
private:
	COORD pos;
	enum Entities//enumeration to store the types of entities
	{
		E_Hunter,
		E_Healer,
		E_NPC,
		E_Boss,
		E_NULL
	};
public:
	Entity(void);
	void setposition(int X, int Y);
	COORD getposition();
	int getX();
	int getY();
};

