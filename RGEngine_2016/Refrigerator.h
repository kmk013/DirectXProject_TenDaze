#pragma once
#include "RGEngine.h"
#include "Sprite.h"
#include "Sound.h"

class Refrigerator : public RGEngine::GameObject
{
public:
	Refrigerator();

	Sprite *closedSpr[2];
	Sprite *openedSpr[2];

	Sprite *caffeine[5][2];
	Sprite *caffeineInfo[5];
	int caffeineCost[5];

	Math::Vector canPos[3];
	float canHeight;

	bool isInit;
	Sound *dopingSound;
	Sound *openSound;
	Sound *closeSound;

	void ChangeState(bool state);
	void OnUpdate(void) override;
};