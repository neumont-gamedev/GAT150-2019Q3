#include "renderer.h"
#include <iostream>

bool Renderer::Startup()
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();

	return true;
}

void Renderer::Shutdown()
{
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
}

void Renderer::Update()
{
	//
}

void Renderer::Create(const std::string& name, int width, int height)
{
	m_window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void Renderer::BeginFrame()
{
	SDL_RenderClear(m_renderer);
}

void Renderer::EndFrame()
{
	SDL_RenderPresent(m_renderer);
}

//void Renderer::SetColor(color color_)
//{
//	SDL_SetRenderDrawColor(m_renderer, color_.convert_u8(0), color_.convert_u8(0), color_.convert_u8(0), 255);
//}
