#include "stdafx.h"

Position PhysicsComponent::movementAction(Position pos, Velocity vel, float time)
{
	pos.x = pos.x + vel.x * time;
	pos.y = pos.y + vel.y * time;
	return pos;
}

Velocity InputComponent::setVelocity(Velocity vel, Velocity vel_val)
{
	if (ctrl.Left == true && ctrl.Right == false)
		vel.x = -vel_val.x;

	if (ctrl.Right == true && ctrl.Left == false)
		vel.x = vel_val.x;

	if ((ctrl.Right == true && ctrl.Left == true) || (ctrl.Right == false && ctrl.Left == false))
		vel.x = 0;

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
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			ctrl.isRunning = false;
		}

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				ctrl.Left = true;
				break;
			case SDLK_SPACE:
				ctrl.Blast = true;
				break;
			case SDLK_RIGHT:
				ctrl.Right = true;
				break;
			default:
				break;
			}
		}

		if (event.type == SDL_KEYUP)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_LEFT:
				ctrl.Left = false;
				break;
			case SDLK_RIGHT:
				ctrl.Right = false;
				break;
			case SDLK_SPACE:
				ctrl.Blast = false;
				break;
			default:
				break;
			}
		}
	}
	return ctrl;
}

GraphicsComponent::GraphicsComponent(unsigned int width, unsigned int height)
{
	Height = height;
	Width = width;
}

void GraphicsComponent::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	m_window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif

	gluOrtho2D(0.0, Width, 0.0, Height);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(m_window);
}

void GraphicsComponent::Destroy()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void GraphicsComponent::drawRectangle(Position V1, Position V2, Position V3, Position V4)
{
	glBegin(GL_QUADS);
		glVertex2f(V1.x , V1.y);
		glVertex2f(V2.x, V2.y);
		glVertex2f(V3.x, V3.y);
		glVertex2f(V4.x, V4.y);
	glEnd();
}

void GraphicsComponent::drawPoint(Position V)
{
	glBegin(GL_POINTS);
		glVertex2f(V.x, V.y);
	glEnd();
}

void GraphicsComponent::drawLine(Position V1, Position V2)
{
	glBegin(GL_LINES);
		glVertex2f(V1.x, V1.y);
		glVertex2f(V2.x, V2.y);
	glEnd();
}

void GraphicsComponent::drawCircle(Position center, float radius)
{
	float degInrad;
	float deg2rad = 3.14159 / 180.0;
	Position head;

	glBegin(GL_LINE_LOOP);
	
			/*if (radius < 0 || radius > 16.0)
				rad.y = -rad.y;*/
			for (int i = 0; i <= 360; i++)
			{
				degInrad = (float)i * deg2rad;
				head.x = cos(degInrad) * radius + center.x;
				head.y = sin(degInrad) * radius + center.y;
				glVertex2f(head.x, head.y);
			}
	glEnd();
}
//void GraphicsComponent::renderAll(vector<Position> blasts, Position hero)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(1, 1, 0);
//	glBegin(GL_LINES);
//	for (int i = 0; i <= blasts.size(); i++)
//	{
//		glVertex2f(blasts[i].x, blasts[i].y);
//		glVertex2f(blasts[i].x, blasts[i].y + Height / 32.0);
//	}
//	glEnd();
//
//	glColor3f(1, 0, 0);
//	glBegin(GL_QUADS);
//
//	glColor3f(1.0, 0.0, 0.0);
//	glVertex2f(pos.x - 32.0, pos.y - 24.0);
//	glVertex2f(pos.x - 32.0, pos.y + 24.0);
//	glVertex2f(pos.x + 32.0, pos.y + 24.0);
//	glVertex2f(pos.x + 32.0, pos.y - 24.0);
//	glEnd();
//
//	glBegin(GL_QUADS);
//	glVertex2f(pos.x - 8.0, pos.y + 24.0);
//	glVertex2f(pos.x - 8.0, pos.y + 36.0);
//	glVertex2f(pos.x + 8.0, pos.y + 36.0);
//	glVertex2f(pos.x + 8.0, pos.y + 24.0);
//	glEnd();
//	glFlush();
//
//}

