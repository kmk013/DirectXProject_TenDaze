#pragma once
#include "RGScene.h"
#include "Sprite.h"
#include "Sound.h"
class MainScene :
	public RGEngine::Scene
{
public:
	Sprite *title;
	Sprite *gameStart;
	Sprite *howToPlay;
	Sprite *collection;
	Sprite *exitButton;

	int howToCnt;
	Sprite *howToEx[3];
	
	Sound *buttonSound;
	Sound *mainBGM;

	Sprite *cursor;

	MainScene();
	~MainScene();

	void OnUpdate() override;
};

