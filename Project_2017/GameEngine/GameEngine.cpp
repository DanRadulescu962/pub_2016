// GameEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char** argv)
{
	World* w = new World(1024, 768, 10);
	w->Start();
	delete w;
	system("PAUSE");
	return 0;
}

