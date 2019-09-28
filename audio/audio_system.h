#pragma once

#include "..\\framework\system.h"

#include "..\\external\fmod\api\core\inc\fmod.hpp"
#include <string>
#include <map>
#include <vector>

class AudioSystem : public System
{
public:
	AudioSystem(Engine* engine) : System(engine) {}
	~AudioSystem() {}

	bool Startup();
	void Shutdown();

	void Update();

	void AddAudio(const std::string& key, const std::string& filename);
	void PlayAudio(const std::string& key, bool loop = false);
	void AudioSound(const std::string& key);

private:
	FMOD::System* m_system;
	std::map<std::string, FMOD::Sound*> m_sounds;
	std::vector<FMOD::Channel*> m_channels;
};