#pragma once
#ifndef PL
#define PL

#include "TEMPLATES.h"

class Player
{
protected:
	int x, y;
public:
	Player();
	Player(int, int);
	void setX(int);
	void setY(int);
	int getX() const;
	int getY() const;
};

#endif