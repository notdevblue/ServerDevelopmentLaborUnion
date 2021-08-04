#include "CEasyServer.h"


int main()
{
	CEasyServer server;
	
	while (true)
	{
		if (server.acceptClient() == -1)
		{
			return(-1);
		}
	}
	
	
	return(0);
}