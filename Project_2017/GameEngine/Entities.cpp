#include "stdafx.h"

World::World(unsigned int width, unsigned int height, unsigned int opps)
{	
	hero = make_unique<Hero>();
	_physics = make_unique<PhysicsComponent>();
	_input = make_unique<InputComponent>();
	_graphics = make_unique<GraphicsComponent>(width, height);

	nr_opponents = opps;
	current_opps = 0;
	anim_radius = 0.0;
	anim_vel = _graphics->Height / 10.0;
	hbar_length = height / 2.0;
	hbar_width = width / 40.0;

	hero->health.value = 30.0;
	hero->health.decrease_rate = 5.0;
	hero->pos.x = _graphics->Width / 2.0;
	hero->pos.y = _graphics->Height / 20.0;
	vel_val.x = _graphics->Width / 2.0;
	vel_val.y = _graphics->Height;
	nr_stars = _graphics->Width * _graphics->Height / 1536;

	_graphics->Init();
	SpawnStaticObjects();
}

void World::Start()
{
	finalTime = clock();
	while (_input->ctrl.isRunning)
	{
		startTime = finalTime;
		finalTime = clock();
		s_time = s_time = ((float)(finalTime - startTime)) / CLOCKS_PER_SEC;

		hero->vel = _input->setVelocity(hero->vel, vel_val);
		updateStatus();
		updatePosition();
		if (nr_opponents > 0)
			SpawnOpponents();
		SpawnBlasts();

		renderAll();

		_input->ctrl = _input->getCommand();
	}
	_graphics->Destroy();
	if (hero->health.value <= 0)
		printf("YOU LOST!\n");
	else
		printf("YOU WON!\n");
}

void World::SpawnStaticObjects()
{
	srand(time(NULL));
	Position adder;
	for (int i = 0; i < nr_stars; i++)
	{
		adder.x = rand() % _graphics->Width;
		adder.y = rand() % _graphics->Height;
		stars.push_back(adder);
	}
}

void World::SpawnBlasts()
{
	RandomMovingObject adder;
	if (_input->ctrl.Blast == true)
	{
		adder.pos.x = hero->pos.x;
		adder.pos.y = hero->pos.y;
		adder.vel.x = hero->vel.x;
		adder.vel.y = vel_val.y;

		blasts.push_back(adder);

		_input->ctrl.Blast = false;
	}
}

void World::SpawnOpponents()
{
	Opponent adder;
	if (current_opps > 3)
		return;

	int nr_add = rand() % 5 + 1;
	current_opps += nr_add;
	nr_opponents -= nr_add;

	for (int i = 1; i <= nr_add; i++)
	{
		adder.pos.y = (float)_graphics->Height;
		adder.pos.x = (float)((rand() % 39) + 1) * _graphics->Width / 40.0;
		adder.vel.x = 0.0;
		adder.vel.y = -(_graphics->Height / 4.0);
		opponents.push_back(adder);
	}
}

void World::updateStatus()
{
	vector<pair<Opponent, Opponent>>::iterator frag_it = fragments.begin();
	while (frag_it != fragments.end())
	{
		if (fabs((*frag_it).first.pos.x - (*frag_it).second.pos.x) > _graphics->Width / 20.0)
		{
			fragments.erase(frag_it);
			frag_it = fragments.begin();
		}
		else
			frag_it++;
	}
	vector<Opponent>::iterator opp_it = opponents.begin(), aux_opp;
	while (opp_it != opponents.end())
	{
		if ((*opp_it).pos.y < _graphics->Height / 80.0)
		{
			hero->health.value -= hero->health.decrease_rate;
			if (hero->health.value <= 0.0)
				_input->ctrl.isRunning = false;
			current_opps--; 
			opponents.erase(opp_it);
			opp_it = opponents.begin();
		}
		else
			opp_it++;
	}
	
	vector<RandomMovingObject>::iterator bl_it = blasts.begin(), aux_bl = blasts.begin();
	Position margin;
	int sw;
	margin.x = _graphics->Width / 40.0;
	margin.y = _graphics->Height / 32.0;

	while (bl_it != blasts.end())
	{
		opp_it = opponents.begin();
		sw = 0;
		while (opp_it != opponents.end())
		{
			if (_physics->isCollision((*bl_it).pos, (*opp_it).pos, margin))
			{
				aux_bl = aux_bl + 1;
				sw = 1;
				current_opps--;

				//destroy animation
				Opponent opp1, opp2;
				opp1.pos = (*opp_it).pos;
				opp2.pos = opp1.pos;
				opp1.vel.y = opp2.vel.y = 0;
				opp1.vel.x = (*opp_it).vel.y / 2.0;
				opp2.vel.x = -opp1.vel.x;
				fragments.push_back(make_pair(opp1, opp2));

				opponents.erase(opp_it);
			    blasts.erase(bl_it);
				break;
			}
			opp_it++;
		}
		if (sw == 0)
		{
			bl_it++;
			aux_bl = bl_it;
		}
		else
		{
			bl_it = blasts.begin();
			//bl_it = aux_bl;
		}
	}

	if (current_opps <= 0 && nr_opponents <= 0)
		_input->ctrl.isRunning = false;
}

void World::updatePosition()
{
	hero->pos = _physics->movementAction(hero->pos, hero->vel, s_time);
	anim_radius = anim_radius + anim_vel * s_time;

	if (hero->pos.x <= _graphics->Width / 20.0)
		hero->pos.x = _graphics->Width / 20.0;
	if (hero->pos.x >= _graphics->Width - _graphics->Width / 20.0)
		hero->pos.x = _graphics->Width - _graphics->Width / 20.0;
	if (anim_radius > _graphics->Height / 60.0)
		anim_vel = -anim_vel;
	if (anim_radius < 0.0)
		anim_vel = -anim_vel;

	for (int i = 0; i < blasts.size(); i++)
		blasts[i].pos = _physics->movementAction(blasts[i].pos, blasts[i].vel, s_time);

	for (int i = 0; i < opponents.size(); i++)
		opponents[i].pos = _physics->movementAction(opponents[i].pos, opponents[i].vel, s_time);

	for (int i = 0; i < fragments.size(); i++)
	{
		fragments[i].first.pos = _physics->movementAction(fragments[i].first.pos, fragments[i].first.vel, s_time);
		fragments[i].second.pos = _physics->movementAction(fragments[i].second.pos, fragments[i].second.vel, s_time);
	}

}

void World::renderAll()
{
	Position aux, aux2, aux3, aux4;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 1, 0);
	for (int i = 0; i < blasts.size(); i++)
	{
		aux.x = blasts[i].pos.x;
		aux.y = blasts[i].pos.y + _graphics->Height / 32.0;
		_graphics->drawLine(blasts[i].pos, aux);
	}

	glColor3f(255, 255, 255);
	for (int i = 0; i < nr_stars; i++)
		_graphics->drawPoint(stars[i]);

	glColor3f(1.0, 0.0, 0.0);

	aux.x = hero->pos.x - _graphics->Width / 20.0;
	aux.y = hero->pos.y - _graphics->Height / 20.0;
	aux2.x = hero->pos.x - _graphics->Width / 20.0;
	aux2.y = hero->pos.y + _graphics->Height / 20.0;
	aux3.x = hero->pos.x + _graphics->Width / 20.0;
	aux3.y = hero->pos.y + _graphics->Height / 20.0;
	aux4.x = hero->pos.x + _graphics->Width / 20.0;
	aux4.y = hero->pos.y - _graphics->Height / 20.0;

	_graphics->drawRectangle(aux, aux2, aux3, aux4);

	aux.x = hero->pos.x - _graphics->Width / 80.0;
	aux.y = hero->pos.y + _graphics->Height / 20.0;
	aux2.x = hero->pos.x - _graphics->Width / 80.0;
	aux2.y = hero->pos.y + _graphics->Height / 14.0;
	aux3.x = hero->pos.x + _graphics->Width / 80.0;
	aux3.y = hero->pos.y + _graphics->Height / 14.0;
	aux4.x = hero->pos.x + _graphics->Width / 80.0;
	aux4.y = hero->pos.y + _graphics->Height / 20.0;

	_graphics->drawRectangle(aux, aux2, aux3, aux4);
	
	glColor3f(0.0, 0.0, 1.0);
	for (int i = 0; i < opponents.size(); i++)
	{
		aux.x = opponents[i].pos.x - _graphics->Width / 80.0;
		aux.y = opponents[i].pos.y - _graphics->Height / 80.0;
		aux2.x = opponents[i].pos.x + _graphics->Width / 80.0;
		aux2.y = opponents[i].pos.y - _graphics->Height / 80.0;
		aux3.x = opponents[i].pos.x + _graphics->Width / 40.0;
		aux3.y = opponents[i].pos.y + _graphics->Height / 80.0;
		aux4.x = opponents[i].pos.x - _graphics->Width / 40.0;
		aux4.y = opponents[i].pos.y + _graphics->Height / 80.0;
		_graphics->drawRectangle(aux, aux2, aux3 ,aux4);

		aux.x = opponents[i].pos.x;
		aux.y = opponents[i].pos.y - _graphics->Height / 80.0;
		_graphics->drawCircle(aux, anim_radius);
	}
	
	for (int i = 0; i < fragments.size(); i++)
	{
		aux.x = fragments[i].first.pos.x - _graphics->Width / 80.0;
		aux.y = fragments[i].first.pos.y - _graphics->Height / 80.0;
		aux2.x = fragments[i].first.pos.x;
		aux2.y = fragments[i].first.pos.y - _graphics->Height / 80.0;
		aux3.x = fragments[i].first.pos.x;
		aux3.y = fragments[i].first.pos.y + _graphics->Height / 80.0;
		aux4.x = fragments[i].first.pos.x - _graphics->Width / 40.0;
		aux4.y = fragments[i].first.pos.y + _graphics->Height / 80.0;
		_graphics->drawRectangle(aux, aux2, aux3, aux4);

		aux.x = fragments[i].second.pos.x + _graphics->Width / 80.0;
		aux.y = fragments[i].second.pos.y - _graphics->Height / 80.0;
		aux2.x = fragments[i].second.pos.x;
		aux2.y = fragments[i].second.pos.y - _graphics->Height / 80.0;
		aux3.x = fragments[i].second.pos.x;
		aux3.y = fragments[i].second.pos.y + _graphics->Height / 80.0;
		aux4.x = fragments[i].second.pos.x + _graphics->Width / 40.0;
		aux4.y = fragments[i].second.pos.y + _graphics->Height / 80.0;
		_graphics->drawRectangle(aux, aux2, aux3, aux4);
	}
	float red_length;
	red_length = hbar_length * ( 1.0 - hero->health.value / 30.0);

	glColor3f(1.0, 0.0, 0.0);
	aux.x = 78 / 80.0 * _graphics->Width;
	aux.y = 3 / 4.0 * _graphics->Height;
	aux2.x = (float)_graphics->Width;
	aux2.y = 3 / 4.0 * _graphics->Height;
	aux3.x = (float)_graphics->Width;
	aux3.y = aux2.y - red_length;
	aux4.x = 78 / 80.0 * _graphics->Width;
	aux4.y = aux2.y - red_length;
	_graphics->drawRectangle(aux, aux2, aux3, aux4);

	glColor3f(0.0, 1.0, 0.0);
	aux.x = 78 / 80.0 * _graphics->Width;
	aux.y = aux2.y - red_length;
	aux2.x = (float)_graphics->Width;
	aux2.y = aux2.y - red_length;
	aux3.x = (float)_graphics->Width;
	aux3.y = _graphics->Height / 4.0;
	aux4.x = 78 / 80.0 * _graphics->Width;
	aux4.y = _graphics->Height / 4.0;
	_graphics->drawRectangle(aux, aux2, aux3, aux4);
	glFlush();

	SDL_GL_SwapWindow(_graphics->m_window);
}