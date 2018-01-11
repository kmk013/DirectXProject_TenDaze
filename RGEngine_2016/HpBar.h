#pragma once
#include "Sprite.h"

class HpBar : public RGEngine::GameObject
{
public:
	HpBar();
	~HpBar();

	bool isInit;
	Sprite *hpBarSprite[12];
	Sprite *tropicanaBar;

	void OnUpdate() override;
};

