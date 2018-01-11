#include "Sound.h"

Sound::Sound(std::string path)
{
	name = "sound";

	audio = AttachComponent<Components::AudioSource>();
	audio->SetSound(path);
}

Sound::~Sound()
{
}
