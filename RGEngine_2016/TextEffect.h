#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class TextEffect : public RGEngine::GameObject
{
public:
	TextEffect(string path);

	Components::SpriteRenderer *sprite;

	void OnUpdate() override;
};