#include "NPC.h"

NPC::NPC()
{
	Advice[0] = { "Remember to heal your beasts regularly." };
	Advice[1] = { "There is no beast centre nearby to revive a beast that has fainted." };
	Advice[2] = { "Fire is super effective against Nature." };
	Advice[3] = { "Nature is strong against Water." };
	Advice[4] = { "Water can defeat Fire easily." };
	Advice[5] = { "Earth is good against Fire but is weak to Water." };
	Healwords = "your Ele-beasts look beat up let me heal them for you";
}

std::string NPC::interact()
{
	return Advice[rand()% 6];
}

std::string NPC::Healquote()
{
	return Healwords;
}

NPC::~NPC()
{

}