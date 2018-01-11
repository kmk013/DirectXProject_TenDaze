#pragma once
#include "RGGameObject.h"
#include "Sprite.h"
#include "Developer.h"
#include "UI.h"
#include "Sound.h"

class Tear :
	public RGEngine::GameObject
{
public:
	bool isSparkling;
	Components::SpriteRenderer * mys;
	float speed=300.0f;
public:
	Tear(bool isSpark);
	~Tear();
	void OnUpdate();
	void TearGain();
	void Sagwatoktoktok();

	Sound *getTearSound;
};

