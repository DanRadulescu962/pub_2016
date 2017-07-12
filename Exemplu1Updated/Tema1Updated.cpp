// Tema1Updated.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TEMPLATES.h"
#include "GameMap.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Map<char> map;
	char s[255];
	int m, n;
	Player Romeo, Juliet, Result;

	cout << "m="; cin >> m;
	cout << "n="; cin >> n;
	map = allocMap<char>(m, n);

	//Building initial matrix
	for (int i = 0; i < m; i++)
	{
		cin.get();
		cin.get(s, 255, '\n');
		for (int j = 0; j < n; j++)
			map[i].get()[j] = s[j];
	}

	//Construct initial map
	GameMap M(map, m, n);
	
	Romeo = M.getPlayerPosition(2);
	Juliet = M.getPlayerPosition(3);
	Result = M.GameResult(Romeo, Juliet);

	//-1 -1 if they don't meet
	cout << Result.getX() << " " << Result.getY()<<'\n';

	
	system("PAUSE");
    return 0;
}

