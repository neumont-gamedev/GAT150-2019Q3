#pragma once

#include "..\\framework\system.h"

#include "..\\external\SDL2-2.0.10\include\SDL.h"
#include "..\\external\SDL2-2.0.10\include\SDL_image.h"
#include "..\\external\SDL2-2.0.10\include\SDL_ttf.h"

#include <string>

class Renderer : public System
{
public:
	Renderer(Engine* engine) : System(engine) {}
	~Renderer() {}
	
	bool Startup();
	void Shutdown();
	void Update();

	void Create(const std::string& name, int width, int height);
	void BeginFrame();
	void EndFrame();

	//void SetColor(color color_);

	SDL_Renderer* GetSDLRenderer() { return m_renderer; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;

	Engine* m_engine = nullptr;
};