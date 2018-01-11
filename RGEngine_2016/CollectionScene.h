#pragma once
#include "RGScene.h"
#include "Sprite.h"
#include "Sound.h"

class CollectionScene : public RGEngine::Scene
{
public:
	CollectionScene();
	~CollectionScene();

	Sprite *collectionBack[2];

	Sprite *smallEnding[6];
	Sprite *bigEnding[6];
	Sprite *endingInfo[6];

	Sprite *smallWhip[6];
	Sprite *bigWhip[6];
	Sprite *whipInfo[6];

	Sprite *backBtn;
	Sprite *nextBtn;
	Sprite *privBtn;
	Sprite *activeImg;

	Sound *buttonSound;
	Sound *collectionBGM;

	Sprite *cursor;

	int selectIndex;

	void OnUpdate() override;
};

