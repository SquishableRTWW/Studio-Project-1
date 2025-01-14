#include "hunter.h"

hunter::hunter(void)
{
	string name = "null";
	for (int i = 0; i < 6; i++)
	{
		party[i].setOGStats();
	}
	direction = 0;
	range = 0;
	check = false;
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
		party[0].setElement("fire");
		for (int i = 0; i < 2; i++)
		{
			party[0].setMove(party[0], i);
		}
		break;
	case 2:
		party[0] = typhis();
		party[0].setElement("water");
		for (int i = 0; i < 2; i++)
		{
			party[0].setMove(party[0], i);
		}
		break;
	case 3:
		party[0] = vitalus();
		party[0].setElement("nature");
		for (int i = 0; i < 2; i++)
		{
			party[0].setMove(party[0], i);
		}
		break;
	}
	party[0].setLevel(5);
}

void hunter::addparty(monster& monster)
{
	for (int i = 1; i < 6; i++)
	{
		if (party[i].getName() == "NULL")
		{
			party[i] = monster;
			break;
		}
	}
}

void hunter::setDirRange(int d, int r)
{
	direction = d;
	range = r;
}

void hunter::setcheck(bool c)
{
	check = c;
}

bool hunter::getcheck(void)
{
	return check;
}

int hunter::getdirection(void)
{
	return direction;
}

int hunter::getrange(void)
{
	return range;
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

void hunter::setMHealth(int i, int j)
{
	monster mon = getMonster(i);
	mon.setHealth(j);
}
void hunter::setMAttack(int i, int j)
{
	getMonster(i).setAttack(j);
}
void hunter::setMDefence(int i, int j)
{
	getMonster(i).setDefence(j);
}
void hunter::setMSpeed(int i, int j)
{
	getMonster(i).setSpeed(j);
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
