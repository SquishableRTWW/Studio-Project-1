#pragma once
#include "Framework/console.h"
class Entity
{
private:
	COORD pos;
public:
	Entity(void);
	void setposition(int X, int Y);
	int getX();
	int getY();
};

