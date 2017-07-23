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

Velocity InputComponent::setVelocity(Velocity vel, Control ctrl, Velocity vel_val)
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

bool PhysicsComponent::OutOfBounds(Position pos, int window_height, int window_width)
{
	if (pos.x <= 0 || pos.x > window_width)
		return true;
	if (pos.y <= 0 || pos.y > window_height)
		return true;
	return false;
}

Control InputComponent::getCommand()
{
	Control ctrl;
	SDL_Event evt;
	while (SDL_PollEvent(&evt))
	{

		switch (evt.type)

		{

		case SDL_KEYDOWN:

		{

			if (evt.key.keysym.sym == SDLK_LEFT)

				ctrl.Left = true;

			if (evt.key.keysym.sym == SDLK_RIGHT)

				ctrl.Right = true;

			if (evt.key.keysym.sym == SDLK_SPACE)

				ctrl.Blast = true;

			break;

		}

		case SDL_KEYUP:

		{
			if (evt.key.keysym.sym == SDLK_LEFT)
				ctrl.Left = false;

			if (evt.key.keysym.sym == SDLK_RIGHT)
				ctrl.Right = false;

			if (evt.key.keysym.sym == SDLK_SPACE)
				ctrl.Blast = false;

			break;

		}

		}
	}
	return ctrl;
}