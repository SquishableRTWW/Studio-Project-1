#pragma once
#include "entity.h"
#include <string>

class NPC :public Entity
{
private:
	std::string Advice[7];
	std::string Healwords;
	std::string Warn;
public:
	NPC(void);
	std::string interact(void);
	std::string Healquote(void);
	std::string warning(void);
	~NPC();
};

