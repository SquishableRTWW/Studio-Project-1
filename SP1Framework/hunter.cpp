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

monster hunter::choosestarter(int s)
{
	if (s == 1)
	{
		party[0] = ignis();
	}
	else if (s == 2)
	{
		party[0] = typhis();
	}
	else if (s == 3)
	{
		party[0] = vitalus();
	}
}

void hunter::addparty(int m)
{
	for (int i = 1; i < 6; i++)
	{
		if (m == 1)
		{
			party[i] = oris();
		}
	}
}

hunter::~hunter(void)
{

}
