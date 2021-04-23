#pragma once
#include <Windows.h>
#include <conio.h>

enum Key
{
	base	= 224,
	up		= 72,
	down	= 80,
	left	= 75,
	right	= 77
};



#pragma region Render
void gotoxy(SHORT x, SHORT y);

#pragma endregion

#pragma region Player
void inputPlayer();
void move(int x, int y);

#pragma endregion
