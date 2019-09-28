#pragma once
#include "render_component.h"
#include "..\\external\SDL2-2.0.10\include\SDL.h"

class SpriteAnimationComponent : public RenderComponent
{
public:
	SpriteAnimationComponent() {}

	void Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin = vector2::zero);
	
	void Initialize() override;
	void Destroy() override;
	bool Load(const rapidjson::Value& value) override;
	Component* Clone() override { return new SpriteAnimationComponent(*this); }

	void Update() override;
	void Draw() override;

private:
	Name m_texture_name;
	vector2 m_origin;
	SDL_Rect m_rect;

	int m_grid_x;
	int m_grid_y;
	int m_num_frames = 0;
	int m_frame = 0;
	float m_frame_timer = 0.0f;
	float m_frame_rate = 0.1f;
};
