#include "font.h"
#include "..\\core\assert.h"

Font::~Font()
{
}

bool Font::Create(const Name& font_name)
{
	m_font = TTF_OpenFont(font_name.c_str(), 32);
	ASSERT(m_font);

	return true;
}

void Font::Destroy()
{
	if (m_font)
	{
		TTF_CloseFont(m_font);
		m_font = nullptr;
	}
}
