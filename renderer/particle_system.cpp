#include "particle_system.h"
#include "..\\core\assert.h"
#include "..\\engine\engine.h"
#include "..\\renderer\renderer.h"
#include "..\\renderer\texture.h"

ParticleSystem::ParticleSystem(Engine* engine) : System(engine)
{
	m_particle_pool = new PoolAllocator<Particle>(1000);
}

ParticleSystem::~ParticleSystem()
{
	delete m_particle_pool;
}

void ParticleSystem::Update()
{
	for (Particle* particle : m_particles)
	{
		particle->lifetime = particle->lifetime - g_timer.dt();
		bool active = (particle->lifetime > 0.0f);
		particle->state[Particle::ACTIVE] = active;
		
		if (particle->state[Particle::ACTIVE])
		{
			particle->position = particle->position + (particle->velocity * g_timer.dt());
			particle->velocity = particle->velocity * std::pow(particle->damping, g_timer.dt());
			if (particle->state[Particle::ORIENT_TO_VELOCITY])
			{
				particle->rotation = vector2::get_angle(particle->velocity) * math::RAD_TO_DEG + 90.0f;
			}
		}
	}

	auto iter = m_particles.begin();
	while (iter != m_particles.end())
	{
		if ((*iter)->state[Particle::ACTIVE] == false)
		{
			(*iter)->state[Particle::ACTIVE] = false;
			m_particle_pool->Free(*iter);
			iter = m_particles.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void ParticleSystem::Draw()
{
	for (Particle* particle : m_particles)
	{
		Texture* texture = m_engine->GetResourceManager()->Get<Texture>(particle->texture_name);
		texture->Draw(particle->position, particle->rotation, vector2::one, vector2(0.5f, 0.5f));
	}
}

void ParticleSystem::Create(const Name& texture_name, const vector2& position, const vector2& velocity, float damping, float lifetime, bit_mask_t state)
{
	Particle* particle = m_particle_pool->Get();
	if (particle)
	{
		particle->texture_name = texture_name;
		particle->state = bit_mask_t(BIT(Particle::ACTIVE)) | state;

		particle->lifetime = lifetime;

		particle->position = position;
		particle->velocity = velocity;
		particle->damping = damping;

		m_particles.push_back(particle);
	}
}

