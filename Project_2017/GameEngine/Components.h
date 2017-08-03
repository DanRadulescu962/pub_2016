#pragma once
#ifndef COMP
#define COMP
#include <iostream>
#include <string>
#include <SDL.h>
using namespace std;

struct Position
{
	float x, y;
};

struct Velocity
{
	float x, y;
};

struct Health
{
	float value, decrease_rate;
};

struct Control
{
	bool Left, Right, Blast, isRunning;
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
	Position movementAction(Position pos, Velocity vel, float time);
	bool isCollision(Position pos1, Position pos2, Position margin);
	bool OutOfBounds(Position pos, int window_height, int window_width);
};


class InputComponent
{
public:
	Control ctrl;
public:
	InputComponent() 
	{
		ctrl.Left = false;
		ctrl.Right = false;
		ctrl.Blast = false;
		ctrl.isRunning = true;
	};
	Velocity setVelocity(Velocity vel, Velocity vel_val);
	Control getCommand();
};

class GraphicsComponent
{
public:
	unsigned int Width, Height;
	SDL_Window* m_window;
	SDL_GLContext m_context;
public:
	GraphicsComponent(unsigned int, unsigned int);
	void Init();
	void Destroy();
	void drawRectangle(Position V1, Position V2, Position V3, Position V4);
	void drawPoint(Position V);
	void drawLine(Position V1, Position V2);
	void drawCircle(Position center, float radius);
};
#endif