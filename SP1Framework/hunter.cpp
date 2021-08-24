#include "hunter.h"

hunter::hunter(void)
{
	string name = "null";
	for (int i = 0; i < 6; i++)
	{
		party[i].setOGStats();
	}
	
}

void hunter::setname(string n)
{
	name = n;
}

string hunter::getname()
{
	return name;
}

void hunter::choosestarter(int s)
{
	switch (s)
	{
	case 1:
		party[0] = ignis();
		break;
	case 2:
		party[0] = typhis();
		break;
	case 3:
		party[0] = vitalus();
		break;
	}
	party[0].setLevel(5);
}

void hunter::addparty(int m)
{
	for (int i = 1; i < 6; i++)
	{
		switch (m)
		{
		case 1:
			party[i] = oris();
			break;
		case 2:
			party[i] = lavarous();
			break;
		case 3:
			party[i] = azure();
			break;
		}
	}
}

monster hunter::getMonster(int m)
{
	return party[m];
}

string hunter::getMname(int i)
{
	return party[i].getName();
}

int hunter::getMlvl(int i)
{
	return party[i].getLevel();
}

int hunter::getMhealth(int i)
{
	return party[i].getHealth();
}

int hunter::getMattack(int i)
{
	return party[i].getAttack();
}

int hunter::getMdefense(int i)
{
	return party[i].getDefence();
}

int hunter::getMspeed(int i)
{
	return party[i].getSpeed();
}

string hunter::getMelement(int i)
{
	return party[i].getElement();
}

int hunter::getMkills(int i)
{
	return party[i].getKills();
}

hunter::~hunter(void)
{

}
