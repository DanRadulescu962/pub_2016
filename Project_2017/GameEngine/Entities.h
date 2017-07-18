#pragma once
#ifndef EN
#define EN

#include "Components.h"
#include <memory>
#include <vector>
using namespace std::tr1;

//GAME ENTITIES

class World
{
public:
	int nr_opponents;
	std::unique_ptr<Hero> hero;
	vector<Opponent>opponents;
	vector<RandomMovingObject>blasts;
	PhysicsComponent _physics;
public:
	World();
};

#endif