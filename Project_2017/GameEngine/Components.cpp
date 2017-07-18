#include "stdafx.h"

Position::Position()
{
	x = 0.0;
	y = 0.0;
}

Position::Position(float dx, float dy)
{
	x = dx;
	y = dy;
}

Position PhysicsComponent::movementAction(Position pos, Velocity vel)
{
	pos.x = pos.x + vel.x;
	pos.y = pos.y + vel.y;
	return pos;
}

Velocity PhysicsComponent::setVelocity(Velocity vel, Control ctrl, Velocity vel_val)
{
	if (ctrl.Left == true && ctrl.Right == false)
	{
		vel.x = -vel_val.x;
	}
	else if (ctrl.Left == false && ctrl.Right == true)
	{
		vel.x = vel_val.x;
	}
	else if ((ctrl.Left == false && ctrl.Right == false) || (ctrl.Left == true && ctrl.Right == true))
	{
		vel.x = 0;
	}
	return vel;
}

bool PhysicsComponent::isCollision(Position pos1, Position pos2, Position margin)
{
	if (fabs(pos1.x - pos2.x) <= margin.x && fabs(pos1.y - pos2.y) <= margin.y)
		return true;
	return false;
}