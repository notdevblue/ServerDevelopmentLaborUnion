#pragma once
#include <WS2tcpip.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "ws2_32")


void movetoInputpos();
void movetoChatpos();

DWORD WINAPI inputThread(LPVOID lpParam);
DWORD WINAPI recvThread(LPVOID lpParam);