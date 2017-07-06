// Tema1POO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "GameMap.h"
#include <cstring>
using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Player Romeo, Juliet;
	char **map, s[255];
	int m, n, x = -1, y = -1;

	cout << "m = "; cin >> m;
	cout << "n = "; cin >> n;

	//build initial char matrix
	map = allocMap<char>(m, n);
	for (int i = 0; i < m; i++)
	{
		cin.get();
		//Am incercat sa pun map[i] in loc de s dar primesc HEAP CORRUPTION DETECTED. Nu imi dau seama din ce cauza.
		cin.get(s, 255, '\n');
		for (int j = 0; j < n; j++)
			map[i][j] = s[j];
	}

	GameMap M(map, m, n);

	M.posPlayer(2, x, y);
	Romeo.setX(x); Romeo.setY(y);

	M.posPlayer(3, x, y);
	Juliet.setX(x); Juliet.setY(y);

	x = -1; y = -1;
	M.GameResult(Romeo.getX(), Romeo.getY(), Juliet.getX(), Juliet.getY(), x, y);

	//-1 -1 if they don't meet
	cout << "They meet at: " << x << " " << y << '\n';
	//erase initial char matrix
	freeMap<char>(m, map);
	system("PAUSE");
    return 0;
}

