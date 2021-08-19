#pragma once
#include <string>
using namespace std;
class moveList
{
private:
	string moves[4];
	int damage[4];
public:
	moveList(void); //Default constructor.
	void setMoveWithName(string move,int position);
	string getMove(int i);
	int getMoveDamage(int i);
	~moveList(void);

};

