#include "stdafx.h"

PlayerEntity::PlayerEntity(Position _pos, Velocity _vel, string name)
{
	pos = _pos;
	vel = _vel;
	app.Name = name;
}

void Opponent::update()
{
	_physics.movementAction(this);
}

void Hero::update()
{
	_physics.movementAction(this);
}

void MovingObject::update()
{
	_physics.movementAction(this);
}

//SUBSYSTEMS

void PhysicsComponent::movementAction(PlayerEntity* object)
{
	if (object->app.Name == "Opponent" || object->app.Name == "Blast")
	{
		object->pos.x += object->vel.x;
		object->pos.y += object->vel.y;
	}
	else if (object->app.Name == "Hero")
	{
		Hero* hero = (Hero*)object;
		if (hero->ctrl.Left == true)
			hero->pos.x -= hero->vel.x;
		else if (hero->ctrl.Right == true)
			hero->pos.x += hero->vel.x;
	}
}