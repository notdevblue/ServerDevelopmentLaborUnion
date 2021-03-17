#include <iostream>

struct Player
{
	std::string name;
	bool isMan;
	int job;
	int exp;
	int hp;
	int mp;
};



int main()
{
	Player pl;
	pl.hp = 100;

	Player pl2;
	pl2.hp = 154;

	printf("%d\r\n", pl.hp);
	printf("%d\r\n", pl2.hp);


	return(0);
}