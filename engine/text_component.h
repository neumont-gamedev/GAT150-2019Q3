#pragma once
#include "render_component.h"

class TextComponent : public RenderComponent
{
public:
	TextComponent() {}

	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new TextComponent(*this); }

	void Update() override;
	void Draw() override;

	void CreateText(const char* text);

private:
	Name m_font_name;
	Name m_texture_name;
	color m_color;
	vector2 m_origin;

	std::string m_text;
	std::string m_texture_name_base;
};
