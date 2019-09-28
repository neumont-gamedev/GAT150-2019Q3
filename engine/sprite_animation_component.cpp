#include "sprite_animation_component.h"
#include "animation_component.h"
#include "entity.h"

#include "..\\renderer\texture.h"

void SpriteAnimationComponent::Create(const Name& name, Entity* owner, const Name& texture_name, const vector2& origin)
{
	m_name = name;
	m_owner = owner;
	m_texture_name = texture_name;
	m_origin = origin;
}

void SpriteAnimationComponent::Initialize()
{
	m_frame = 0;
	m_frame_timer = 0.0f;
	m_frame_rate = 1.0f / 30.0f;
}

void SpriteAnimationComponent::Destroy()
{
}

bool SpriteAnimationComponent::Load(const rapidjson::Value& value)
{
	RenderComponent::Load(value);

	json::get_int(value, "grid_x", m_grid_x);
	json::get_int(value, "grid_y", m_grid_y);
	json::get_int(value, "num_frames", m_num_frames);

	json::get_name(value, "texture_name", m_texture_name);
	json::get_vector2(value, "origin", m_origin);

	return true;
}

void SpriteAnimationComponent::Update()
{
	AnimationComponent* component = m_owner->GetComponent<AnimationComponent>();

	component->SetTimeScaleFrame(25);
	float time = component->GetTime();
	m_frame = static_cast<int>(time * m_num_frames);
	//m_frame_timer += g_timer.dt();
	//while (m_frame_timer >= m_frame_rate)
	//{
	//	m_frame_timer -= m_frame_rate;
	//	m_frame++;
	//	if (m_frame > m_num_frames)
	//	{
	//		m_frame = 0;
	//	}
	//}

	Texture* texture = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);
	vector2 texture_size = texture->GetSize();

	vector2 v(m_grid_x, m_grid_y);
	vector2 frame_size = texture_size / v;

	m_rect.x = static_cast<int>((m_frame % (m_grid_x)) * frame_size.x);
	m_rect.y = static_cast<int>((m_frame / (m_grid_y)) * frame_size.y);
	m_rect.w = static_cast<int>(frame_size.x);
	m_rect.h = static_cast<int>(frame_size.y);
}

void SpriteAnimationComponent::Draw()
{
	Texture* texture = m_owner->GetOwner()->GetEngine()->GetResourceManager()->Get<Texture>(m_texture_name);
	texture->Draw(m_rect, m_owner->m_transform.translation, m_owner->m_transform.rotation * math::RAD_TO_DEG, m_owner->m_transform.scale, vector2(0.5f, 0.5f));
}
