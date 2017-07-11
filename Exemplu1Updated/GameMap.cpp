#include "stdafx.h"
#include "GameMap.h"

GameMap::GameMap(Map<char> a, int m, int n)
{
	mX = m;
	nY = n;

	//build initial map: 0 accesible position, -1 inaccesible pos, 2 for Romeo
	// 3 for Juliet
	InMap = allocMap<int>(m, n);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] == 'X')
				InMap[i][j] = -1;
			else if (a[i][j] == 'R')
				InMap[i][j] = 2;
			else if (a[i][j] == 'J')
				InMap[i][j] = 3;
			else
				InMap[i][j] = 0;
}

GameMap::~GameMap()
{

}

Player GameMap::getPlayerPosition(int nrPlayer)
{
	Player result;
	for (int i = 0; i < mX; i++)
		for (int j = 0; j < nY; j++)
			if (InMap[i][j] == nrPlayer)
			{
				result.setX(i);
				result.setY(j);
				break;
			}
	return result;
}

Map<int> GameMap::setPlayerMatrix()
{
	Map<int> a;
	a = allocMap<int>(mX, nY);

	for (int i = 0; i < mX; i++)
		for (int j = 0; j < nY; j++)
			if (InMap[i][j] != -1)
				a[i][j] = 0;
			else
				a[i][j] = -1;
	return a;
}

Map<int> GameMap::Lee(Player pl, Map<int> m)
{
	assert(pl.getX() != -1 && "Error! Player doesn't exist\n");
	assert(pl.getY() != -1 && "Error! Player doesn't exist\n");
	Map<int> aux = m;
	int p, u, in, jn, dn;
	vector<queue>V;
	queue elem, elem2;
	int dl[4] = { -1, 0, 1, 0 };
	int dc[4] = { 0, 1, 0, -1 };

	elem.x = pl.getX(); elem.y = pl.getY(); elem.d = 1;
	aux[elem.x][elem.y] = 1;
	p = u = 0;
	V.push_back(elem);
	while (p <= u)
	{
		elem = V[p];
		for (int i = 0; i < 4; i++)
		{
			in = elem.x + dl[i];
			jn = elem.y + dc[i];
			dn = 1 + elem.d;
			if (0 <= in && in < mX && 0 <= jn && jn < nY && aux[in][jn] == 0)
			{
				aux[in][jn] = dn;
				u++;
				elem2.x = in; elem2.y = jn; elem2.d = dn;
				V.push_back(elem2);
			}
		}
		p++;
	}
	return aux;
}

Player GameMap::GameResult(Player Romeo, Player Juliet)
{
	RomeoMap = setPlayerMatrix();
	JulietMap = setPlayerMatrix();
	Player Result;
	Result.setX(-1); Result.setY(-1);
	if (RomeoMap.empty() || JulietMap.empty())
	{
		cout << "Player is missing!"; __debugbreak;
		return Result;
	}

	RomeoMap = Lee(Romeo, RomeoMap);
	JulietMap = Lee(Juliet, JulietMap);

	int Min = MAX_INF;
	for (int i = 0; i < mX; i++)
	{
		for (int j = 0; j < nY; j++)
			if (RomeoMap[i][j] == JulietMap[i][j] && RomeoMap[i][j] != -1 && RomeoMap[i][j] != 0 && Min > RomeoMap[i][j])
			{
				Min = RomeoMap[i][j];
				Result.setX(i); Result.setY(j);
			}
	}
	return Result;
}
