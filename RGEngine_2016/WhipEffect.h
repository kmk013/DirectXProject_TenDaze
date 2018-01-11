#pragma once
#include "RGGameObject.h"
#include "Sprite.h"

class WhipEffect : public RGEngine::GameObject
{
	struct Particle
	{
		Sprite *spr;
		Math::Vector speed;
		float gravity;
	};

public:
	WhipEffect(Math::Vector pos, string path, int amount);

	bool isInit;
	list<Particle> particleList;

	void OnUpdate() override;
};
