#pragma once
#include "entity.h"
#include <string>

class NPC :public Entity
{
private:
	std::string Advice[6];
	std::string Healquote;
public:
	NPC();
	std::string interact();
	std::string Healer();
	~NPC();
};

