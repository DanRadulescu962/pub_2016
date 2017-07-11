#pragma once
#ifndef GM
#define GM

#define MAX_INF 10000000
#include "TEMPLATES.h"
#include "Player.h"
#include <assert.h>

struct queue
{
	int x, y, d;
};

class GameMap
{
protected:
	int mX, nY;
	Map<int> InMap, RomeoMap, JulietMap;
public:
	GameMap(Map<char>, int , int);
	~GameMap();
	Player getPlayerPosition(int nrP);
	Map<int> setPlayerMatrix();
	Map<int> Lee(Player, Map<int>);
	Player GameResult(Player, Player);
};

#endif


