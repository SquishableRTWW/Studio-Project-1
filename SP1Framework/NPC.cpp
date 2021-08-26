#include "NPC.h"
#include "game.h"

NPC::NPC(void)
{
	Advice[0] = { "Remember to heal your beasts regularly." };
	Advice[1] = { "There is no beast centre nearby to revive a beast that has fainted." };
	Advice[2] = { "Fire is super effective against Nature." };
	Advice[3] = { "Nature is strong against Water." };
	Advice[4] = { "Water can defeat Fire easily." };
	Advice[5] = { "Earth is good against Fire but is weak to Water." };
	Advice[6] = { "The second attack increases your beasts attack" };
	Healwords = "your Ele-beasts look beat up let me heal them for you";
	Warn = "The boss is ahead turn back now if you are not ready";
}

std::string NPC::interact(void)
{
	return Advice[rand()% 6];
}

std::string NPC::Healquote(void)
{
	return Healwords;
}

std::string NPC::warning(void)
{
	return Warn;
}

NPC::~NPC()
{

}