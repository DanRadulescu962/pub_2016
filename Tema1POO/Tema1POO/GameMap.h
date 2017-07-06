#pragma once
#ifndef GM
#define GM

#define MAX_INF 10000000
#include <iostream>
#include "stdlib.h"
#include "TEMPLATES.h"

struct queue
{
	int x, y, d;
};

class GameMap
{
private:
	int **InMap, mX, nY, **RomeoMap, **JulietMap;
public:
	GameMap(char **a, int m, int n);
	~GameMap();
	void posPlayer(int nrP, int &X, int &Y) const;
	int** setPlayerMatrix();
	void Lee(int sX, int sY, int ***map);
	void GameResult(int sXR, int sYR, int sXJ, int sYJ, int &Coord_x, int &Coord_y);
};

#endif
