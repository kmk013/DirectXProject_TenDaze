#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Sprite : public RGEngine::GameObject
{
public:
	Components::SpriteRenderer *sprite;
	
public:
	Sprite(std::string path);
	~Sprite() override;
};

