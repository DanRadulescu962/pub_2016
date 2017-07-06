#pragma once
#ifndef PL
#define PL
#include <iostream>
#include <stdlib.h>

class Player
{
private:
	int X, Y;
public:
	Player();
	Player(int, int);
	int getX() const;
	int getY() const;
	void setX(int);
	void setY(int);
};

#endif