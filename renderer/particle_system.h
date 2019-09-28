#pragma once

#include "particle.h"
#include "..\\framework\system.h"
#include "..\\core\pool_allocator.h"

class ParticleSystem : public System
{
public:
	ParticleSystem(Engine* engine);
	~ParticleSystem();
	
	void Update() override;
	void Draw();

	void Create(const Name& texture_name, const vector2& position, const vector2& velocity, float damping, float lifetime, bit_mask_t state = bit_mask_t());

protected:
	PoolAllocator<Particle>* m_particle_pool;
	std::list<Particle*> m_particles;
};
