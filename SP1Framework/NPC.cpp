#include "NPC.h"
#include "game.h"

NPC::NPC()
{
	Phrase = rand() % 6;
	Advice[0] = { "Remember to heal your beasts regularly." };
	Advice[1] = { "There is no beast centre nearby to revive a beast that has fainted." };
	Advice[2] = { "Fire is super effective against Nature." };
	Advice[3] = { "Nature is strong against Water." };
	Advice[4] = { "Water can defeat Fire easily." };
	Advice[5] = { "Earth is good against Fire but is weak to Water." };
}

std::string NPC::interact()
{
	return Advice[Phrase];
}

NPC::~NPC()
{

}