#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Animation : public RGEngine::GameObject
{
public:
	Animation();
	~Animation() override;

	void SetCollider();

	Components::AnimationRenderer *ani;
};

