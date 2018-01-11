#include "HpBar.h"
#include "RGEngine.h"
#include "RGApplication.h"
#include "GameScene.h"
using namespace RGEngine;

HpBar::HpBar() : isInit(false)
{
	Math::Vector pos = Math::Vector(900, 970);
	for (int i = 0; i < 12; i++) {
		if (i / 4 == 0) {
			hpBarSprite[i] = new Sprite("resources/GameScene/HpBar/HpBar_1.png");
		}
		else if (i / 4 == 1) {
			hpBarSprite[i] = new Sprite("resources/GameScene/HpBar/HpBar_2.png");
		}
		else if (i / 4 == 2) {
			hpBarSprite[i] = new Sprite("resources/GameScene/HpBar/HpBar_3.png");
		}
		hpBarSprite[i]->position = pos;
		pos.x += 40;
		pos.y -= 20;
	}

	tropicanaBar = new Sprite("resources/GameScene/Sparkling/RainbowBar.png");
	tropicanaBar->position.SetVector(900, 750);
	tropicanaBar->SetEnabled(false);
}

HpBar::~HpBar()
{
}

void HpBar::OnUpdate() {
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	if (!isInit)
	{
		isInit = true;
		for (int i = 0; i < 12; i++)
			gameScene->PushBackGameObject(hpBarSprite[i]);
		gameScene->PushBackGameObject(tropicanaBar);
	}

	for (int i = 0; i < 12; i++)
	{
		if(i <= 12 * gameScene->developer->hp / gameScene->developer->maxHp)
			hpBarSprite[i]->SetEnabled(true);
		else
			hpBarSprite[i]->SetEnabled(false);
	}
}