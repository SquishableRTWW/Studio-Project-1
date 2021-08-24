#include "Entity.h"

Entity::Entity(void)
{
	pos.X = -1;
	pos.Y = -1;
}

void Entity::setposition(int X, int Y)
{
	pos.X = X;
	pos.Y = Y;
}

COORD Entity::getposition()
{
	return pos;
}

int Entity::getX()
{
	return pos.X;
}

int Entity::getY()
{
	return pos.Y;
}
