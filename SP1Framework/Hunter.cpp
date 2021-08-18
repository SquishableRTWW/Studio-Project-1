#include "Hunter.h"

void Hunter::Huntername(std::string name)
{
	Name = name;
}

std::string Hunter::getHuntername()
{
	return Name;
}
