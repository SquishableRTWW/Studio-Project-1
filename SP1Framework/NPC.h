#pragma once
#include "entity.h"
#include <string>

class NPC :public Entity
{
private:
	std::string Advice[6];
public:
	NPC();
	std::string interact();
	~NPC();
};

