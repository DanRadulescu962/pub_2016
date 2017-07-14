#pragma once
#ifndef COMP
#define COMP
#include <iostream>
#include <string>
using namespace std;

struct Position
{
	float x, y;
};

struct Velocity
{
	float x, y;
};

struct Appearance
{
	string Name;
};

struct Health
{
	int value, decrease_rate;
};

struct Control
{
	bool Left, Right, Blast;
};

#endif