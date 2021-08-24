#pragma once
#include "entity.h"
#include <string>

class NPC :public Entity
{
private:
	std::string Advice[6];
	int Phrase;
public:
	NPC();
	std::string interact();
	~NPC();
};

