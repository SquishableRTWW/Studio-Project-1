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

hunter::~hunter(void)
{

}
