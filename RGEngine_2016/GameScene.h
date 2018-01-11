#pragma once
#include "RGScene.h"

#include "Sprite.h"
#include "Sound.h"

#include "HpBar.h"
#include "Developer.h"
#include "Timer.h"
#include "Refrigerator.h"
#include "UI.h"

#include "GameManager.h"

class GameScene : public RGEngine::Scene
{
public:

	HpBar *hpBar;
	Timer *myTimer;

	list<Sprite*> canList;

	Developer *developer;
	Refrigerator *refrigerator;
	UI *ui;

	bool isTropicanaTime;
	std::pair<float, float> tropicanaTimer;
	float tropicanaSpeed;

	bool isAutoClick;
	bool isBlueScreen;
	bool isFinish;

	EndingType goToEndingType;

	Sprite *cursor;
	bool initC;
	float timerC;

	Sound *mainBGM;
	Sound *tropicanaBGM;
public:
	GameScene();
	~GameScene();

	void OnUpdate(void) override;
};