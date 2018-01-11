#pragma once
#include "RGEngine.h"

#include "SoundTest.h"

class MySound : public RGEngine::GameObject
{
public:
	MySound();
	~MySound();

	SoundTest *jump;
	SoundTest *bow;
	SoundTest *gun;
	SoundTest *main;
};

