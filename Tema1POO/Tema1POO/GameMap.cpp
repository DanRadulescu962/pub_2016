#include "stdafx.h"
#include "GameMap.h"
#include <vector>
using namespace std;

GameMap::GameMap(char** a, int m, int n)
{
	mX = m;
	nY = n;

	//build initial map: 0 accesible position, -1 inaccesible pos, 2 for Romeo
	// 3 for Juliet
	InMap = allocMap<int>(m, n);
	RomeoMap = NULL;
	JulietMap = NULL;

	if (InMap != NULL)

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
	if (InMap != NULL) freeMap<int>(mX, InMap);
	if (RomeoMap != NULL) freeMap<int>(mX, RomeoMap);
	if (JulietMap != NULL) freeMap<int>(mX, JulietMap);
}

void GameMap::posPlayer(int nrP, int &x, int &y) const
{
	for (int i = 0; i < mX; i++)
		for (int j = 0; j < nY; j++)
			if (InMap[i][j] == nrP)
			{
				x = i;
				y = j;
				break;
			}
}

int** GameMap::setPlayerMatrix()
{
	int **a;
	a = allocMap<int>(mX, nY);

	if (a != NULL)
		for (int i = 0; i < mX; i++)
			for (int j = 0; j < nY; j++)
				if (InMap[i][j] != -1)
					a[i][j] = 0;
				else
					a[i][j] = -1;
	return a;
}

void GameMap::Lee(int sX, int sY, int*** map)
{
	if (sX == -1 || sY == -1)
	{
		cout << "Player doesn't exist\n";
		return;
	}
	int **aux = *map, p, u, in, jn, dn;
	vector<queue>V;
	queue elem, elem2;
	int dl[4] = {-1, 0, 1, 0};
	int dc[4] = {0, 1, 0, -1};

	elem.x = sX; elem.y = sY; elem.d = 1;
	aux[sX][sY] = 1;
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
	*map = aux;
}

void GameMap::GameResult(int sXR, int sYR, int sXJ, int sYJ, int &Coord_x, int &Coord_y)
{
	RomeoMap = setPlayerMatrix();
	JulietMap = setPlayerMatrix();
	if (RomeoMap == NULL || JulietMap == NULL)
	{
		Coord_x = -1; Coord_y = -1;
		return;
	}

	Lee(sXR, sYR, &RomeoMap);
	Lee(sXJ, sYJ, &JulietMap);

	int Min = MAX_INF;
	for (int i = 0; i < mX; i++)
	{
		for (int j = 0; j < nY; j++)
			if (RomeoMap[i][j] == JulietMap[i][j] && RomeoMap[i][j] != -1 && Min > RomeoMap[i][j])
			{
				Min = RomeoMap[i][j];
				Coord_x = i; Coord_y = j;
			}
	}
}