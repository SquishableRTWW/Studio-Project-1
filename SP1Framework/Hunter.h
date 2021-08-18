#pragma once
#include <string>
#include "monster.h"
class Hunter : public monster
{
private:
	std::string Name;
	monster Party[6];
public:
	void Huntername(std::string name);
	std::string getHuntername();
};

