#pragma once
#ifndef EN
#define EN

#include "Components.h"
#include <time.h>
#include <memory>
#include <vector>
using namespace std::tr1;

//GAME ENTITIES

class World
{
public:
	int nr_opponents, nr_stars, current_opps;
	Velocity vel_val;
	float s_time, anim_radius, anim_vel, hbar_length, hbar_width;
	clock_t startTime, finalTime;

	std::unique_ptr<Hero> hero;
	vector<Opponent> opponents;
	vector< pair<Opponent, Opponent> >fragments;
	vector<RandomMovingObject> blasts;
	vector<Position> stars;
	std::unique_ptr<PhysicsComponent> _physics;
	std::unique_ptr<InputComponent> _input;
	std::unique_ptr<GraphicsComponent> _graphics;
	
public:
	World(unsigned int, unsigned int, unsigned int);
	void Start();
	void SpawnStaticObjects();
	void SpawnBlasts();
	void updatePosition();
	void renderAll();
	void SpawnOpponents();
	void updateStatus();
};

#endif