#pragma once

#include "renderer.h"
#include "..\\renderer\font.h"
#include "..\\renderer\color.h"

#include "..\\resources\resource.h"
#include "..\\core\name.h"
#include "..\\math\vector2.h"

class Texture : public Resource
{
public:
	Texture(Renderer* renderer) : m_renderer(renderer) {}
	~Texture();

	bool Create(const Name& image_name);
	bool CreateFromFont(const Font& font, const char* string, const color& font_color);

	void Destroy();

	void Draw(const SDL_Rect& rect, const vector2& position, float angle = 0, const vector2 & scale = vector2::one, const vector2 & origin = vector2::zero);
	void Draw(const vector2& position, float angle = 0, const vector2& scale = vector2::one, const vector2 & origin = vector2::zero);
	vector2 GetSize() const;

protected:
	Renderer* m_renderer;
	SDL_Texture* m_texture = nullptr;
};