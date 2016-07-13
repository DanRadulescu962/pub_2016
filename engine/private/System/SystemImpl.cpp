#include <Engine/System/System.h>
#include <Engine/Rendering/OpenGLRenderer.h>
#include "System/SystemImpl.h"

namespace Engine
{


void SystemImpl::Init(SCreationSettings&& cs)
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);
	m_window = SDL_CreateWindow(cs.windowTitle, 100, 100, cs.windowWidth, cs.windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	m_context = SDL_GL_CreateContext(m_window);
	//if (cs.hideWindow)
	//	SDL_HideWindow(m_window);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	glEnable(GL_TEXTURE_2D);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
	m_renderer = new Renderer();
	m_renderer->Init();
	m_renderer->OnResize(cs.windowWidth, cs.windowHeight);
}

void SystemImpl::Start()
{
	bool done = false;
	int posX = 64;
	int posY = 64;
	int speed = 3;
	while (!done) {
		m_renderer->BeginFrame();
		Engine::Texture* tex = Engine::Texture::LoadTexture("characters.tga");
		m_renderer->RenderSprite(Sprite(tex, 275,41, 275+16, 41+20), posX, posY);
		SDL_Event evt;
		while (SDL_PollEvent(&evt)) {
			switch (evt.type)
			{
			case SDL_KEYDOWN:
			{
				if (evt.key.keysym.sym == SDLK_UP)
					posY -= speed;
				if (evt.key.keysym.sym == SDLK_DOWN)
					posY += speed;
				if (evt.key.keysym.sym == SDLK_LEFT)
					posX -= speed;
				if (evt.key.keysym.sym == SDLK_RIGHT)
					posX += speed;
				break;
			}
			case SDL_KEYUP:
			{

				break;
			}
			case SDL_WINDOWEVENT:
				switch (evt.window.event) {
				case SDL_WINDOWEVENT_RESIZED:
				{
					SDL_Window *window = SDL_GetWindowFromID(evt.window.windowID);
					int w, h;
					SDL_GetWindowSize(window, &w, &h);
					m_renderer->OnResize(w, h);
					break;
				}
				case SDL_WINDOWEVENT_CLOSE:
				{
					SDL_Window *window = SDL_GetWindowFromID(evt.window.windowID);
					if (window)
					{
						SDL_DestroyWindow(window);
					}
					break;
				}
				break;
				}
				break;
			}
		}
		m_renderer->EndFrame();
		SDL_GL_MakeCurrent(m_window, m_context);
		SDL_GL_SwapWindow(m_window);


	}
};

}