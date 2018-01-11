#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Sound : public RGEngine::GameObject
{
public:
	Components::AudioSource *audio;

public:
	Sound(std::string path);
	~Sound() override;

};

