#pragma once
#include "RGEngine.h"
#include "Sprite.h"
#include "Animation.h"

class UI : public RGEngine::GameObject
{
public:
	UI();

	bool isInit;

	Sprite *tearText[2][10];
	Sprite *developText[2][10];

	Sprite *blackScreen;	
	Animation *tropScreen;
	Sprite *nextDay[10];

	Sprite *realBlackScreen;

	void OnUpdate();
};

