#include "LaborGame.h"

void gotoxy(SHORT x, SHORT y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void inputPlayer()
{
	char input = 0;
	input = _getch();


	if (input == Key::base)
	{
		input = _getch();
		switch (input)
		{
		case Key::up:
			move(0, -1);
			break;

		case Key::down:
			move(0, 1);
			break;

		case Key::left:
			move(-1, 0);
			break;

		case Key::right:
			move(1, 0);
			break;
		}
	}
}

void move(int x, int y)
{

}