#pragma once
#ifndef EN
#define EN

#include "Components.h"

//GAME ENTITIES

class PlayerEntity
{
public:
	Position pos;
	Velocity vel;
	Appearance app;
public:
	PlayerEntity(Position, Velocity, string);
	virtual void update();
protected:
	//GraphicsComponent _graphics;
	//ScriptableComponent _script;
};

class Opponent:public PlayerEntity
{
public:
	Health health;
public:
	Opponent(Health _health, Position _pos, Velocity _vel, string _name) : PlayerEntity(_pos, _vel, _name)
	{
		health = _health;
	}
	void update();
protected:
	PhysicsComponent _physics;
};

class Hero:public PlayerEntity
{
public:
	Health health;
	Control ctrl;
public:
	Hero(Health _health, Position _pos, Velocity _vel, string _name, Control _ctrl) : PlayerEntity(_pos, _vel, _name)
	{
		health = _health;
		ctrl = _ctrl;
	}
	void update();
protected:
	PhysicsComponent _physics;
};

class MovingObject :public PlayerEntity
{
public:
	void update();
protected:
	PhysicsComponent _physics;
};

//SUBSYSTEMS

class PhysicsComponent
{
public:
	void movementAction(PlayerEntity*);
};

#endif