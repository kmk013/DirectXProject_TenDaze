#pragma once
#include "RGScene.h"
#include "Sprite.h"
#include "Sound.h"

class EndingScene : public RGEngine::Scene
{
public:
	
	EndingScene(EndingType type);
	~EndingScene();

	Sprite *developText[3][10];
	Sprite *hitDeveloperText[4][10];
	Sprite *sleepText[3][10];
	Sprite *tearText[2][10];
	Sprite *drinkText[2][10];
	Sprite *endingInfo;

	Sprite *replayBtn;
	Sprite *continueBtn;

	Sprite *realBlackScreen;

	Sound *endingBGM;

	Sprite *cursor;

	void OnUpdate() override;
	void Save(EndingType type);
	void Reset();
};

