#include "CUI.h"

void movetoInputpos()
{

}

void movetoChatpos()
{

}



DWORD WINAPI inputThread(LPVOID lpParam)
{
	movetoInputpos();



	return(0);
}


DWORD WINAPI recvThread(LPVOID lpParam)
{
	movetoChatpos();




	return(0);
}