#pragma once

#include "renderer.h"
#include "..\\renderer\color.h"
#include "..\\resources\resource.h"
#include "..\\core\name.h"

class Font : public Resource
{
public:
	Font(Renderer* renderer) : m_renderer(renderer) {}
	~Font();

	bool Create(const Name& font_name);
	void Destroy();
	
	friend class Texture;

protected:
	Renderer* m_renderer;
	TTF_Font* m_font = nullptr;
};