#pragma once
#ifndef COMP
#define COMP
#include <iostream>
#include <string>
using namespace std;

class Position
{
public:
	float x, y;
public:
	Position();
	Position(float dx, float dy);
};

struct Velocity
{
	float x, y;
};

struct Health
{
	int value, decrease_rate;
};

struct Control
{
	bool Left, Right, Blast;
};

struct Hero
{
	Position pos;
	Velocity vel;
	Control ctrl;
	Health health;
	string name;
};

struct Opponent
{
	Position pos;
	Velocity vel;
	Health health;
	string name;
};

struct RandomMovingObject
{
	Position pos;
	Velocity vel;
	string name;
};

//SUBSYSTEMS

class PhysicsComponent
{
public:
	PhysicsComponent() {};
	Position movementAction(Position pos, Velocity vel);
	bool isCollision(Position pos1, Position pos2, Position margin);
	bool OutOfBounds(Position pos, int window_height, int window_width);
};


class InputComponent
{
public:
	InputComponent() {};
	Velocity setVelocity(Velocity vel, Control ctrl, Velocity vel_val);
	Control getCommand();
};

#endif