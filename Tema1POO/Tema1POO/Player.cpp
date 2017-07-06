#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	X = -1;
	Y = -1;
}

Player::Player(int nX, int nY)
{
	X = nX;
	Y = nY;
}

int Player::getX() const
{
	return X;
}

int Player::getY() const
{
	return Y;
}

void Player::setX(int nX)
{
	X = nX;
}

void Player::setY(int nY)
{
	Y = nY;
}