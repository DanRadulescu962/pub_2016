#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	x = -1;
	y = -1;
}

Player::Player(int nX, int nY)
{
	x = nX;
	y = nY;
}

void Player::setX(int nX)
{
	x = nX;
}

void Player::setY(int nY)
{
	y = nY;
}

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}