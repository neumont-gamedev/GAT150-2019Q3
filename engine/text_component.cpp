#include "text_component.h"
#include "entity.h"

#include "..\\renderer\font.h"


void TextComponent::Initialize()
{
	Font* font = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Font>(m_font_name);
	Texture* texture = new Texture(m_owner->GetOwner()->GetEngine()->GetSystem<Renderer>());

	m_texture_name = Name(m_texture_name_base.c_str(), true);
	m_owner->GetOwner()->GetEngine()->GetResourceManager()->Add(m_texture_name, texture);

	CreateText(m_text.c_str());
}

void TextComponent::Destroy()
{
	m_owner->GetOwner()->GetEngine()->GetResourceManager()->Remove(m_texture_name);
}

bool TextComponent::Load(const rapidjson::Value& value)
{
	RenderComponent::Load(value);

	json::get_name(value, "font_name", m_font_name);
	json::get_color(value, "color", m_color);
	json::get_vector2(value, "origin", m_origin);

	json::get_string(value, "texture_name_base", m_texture_name_base);
	json::get_string(value, "text", m_text);

	return true;
}

void TextComponent::Update()
{
	//
}

void TextComponent::Draw()
{
	Texture* texture = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);
	texture->Draw(m_owner->m_transform.translation, m_owner->m_transform.rotation * math::RAD_TO_DEG, m_owner->m_transform.scale, m_origin);
}

void TextComponent::CreateText(const char* string)
{
	m_text = string;

	Font* font = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Font>(m_font_name);
	Texture* texture = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);

	texture->CreateFromFont(*font, m_text.c_str(), m_color);
}
