#include "texture.h"

Texture::~Texture()
{
	Destroy();
}

bool Texture::Create(const Name& image_name)
{
	SDL_Surface* surface = IMG_Load(image_name.c_str());
	ASSERT(surface);
	m_texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
	ASSERT(m_texture);
	SDL_FreeSurface(surface);

	return true;
}

bool Texture::CreateFromFont(const Font& font, const char* string, const color& font_color)
{
	SDL_Color c;
	c.r = static_cast<Uint8>(font_color.r * 255.0f);
	c.g = static_cast<Uint8>(font_color.g * 255.0f);
	c.b = static_cast<Uint8>(font_color.b * 255.0f);
	c.a = 255;

	SDL_Surface* surface = TTF_RenderText_Solid(font.m_font, string, c);
	ASSERT(surface);
	m_texture = SDL_CreateTextureFromSurface(m_renderer->GetSDLRenderer(), surface);
	SDL_FreeSurface(surface);

	return (m_texture != nullptr);
}

void Texture::Destroy()
{
	if (m_texture)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}

void Texture::Draw(const SDL_Rect& rect, const vector2& position, float angle, const vector2& scale, const vector2& origin)
{
	vector2 size = GetSize();
	size = size * scale;
	vector2 screen_position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(screen_position.x);
	dest.y = static_cast<int>(screen_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_texture, &rect, &dest, angle, nullptr, SDL_FLIP_NONE);
}

void Texture::Draw(const vector2& position, float angle, const vector2& scale, const vector2& origin)
{
	vector2 size = GetSize();
	size = size * scale;
	vector2 screen_position = position - (size * origin);

	SDL_Rect dest;
	dest.x = static_cast<int>(screen_position.x);
	dest.y = static_cast<int>(screen_position.y);
	dest.w = static_cast<int>(size.x);
	dest.h = static_cast<int>(size.y);

	SDL_RenderCopyEx(m_renderer->GetSDLRenderer(), m_texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
}

vector2 Texture::GetSize() const
{
	SDL_Point point;
	SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

	return vector2(point.x, point.y);
}
