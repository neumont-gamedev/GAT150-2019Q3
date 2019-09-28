#pragma once

#include "renderer.h"
#include "..\\resources\resource.h"
#include "..\\core\name.h"
#include "..\\math\vector2.h"
#include "..\\renderer\color.h"

class Text : public Resource
{
public:
	Text(Renderer* renderer) : m_renderer(renderer) {}
	Text(Renderer* renderer, const color& color, int font_size) :
		m_renderer(renderer),
		m_color(color)
	{}

	~Text();

	bool Create(const Name& font_name);
	void Destroy();

	void Draw(const vector2& position, float angle = 0, const vector2& scale = vector2::one, const vector2 & origin = vector2::zero);
	vector2 GetSize() const;

	void SetText(const char* string);
	void SetColor(color c) { m_color = c; }
	const color& GetColor() const { return m_color; }

protected:
	color m_color;

	Renderer* m_renderer;
	TTF_Font* m_font = nullptr;
	SDL_Texture* m_texture = nullptr;
};