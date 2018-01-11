#include "Refrigerator.h"
#include "GameManager.h"
#include "GameScene.h"
#include "TextEffect.h"

using namespace RGEngine;

Refrigerator::Refrigerator() : isInit(false)
{
	closedSpr[NORMAL] = new Sprite("resources/GameScene/Refrigerator/Refrigerator.png");
	closedSpr[NORMAL]->position = Math::Vector(380, 330);
	openedSpr[NORMAL] = new Sprite("resources/GameScene/Refrigerator/Refrigerator_Door.png");
	openedSpr[NORMAL]->SetEnabled(false);
	openedSpr[NORMAL]->position = Math::Vector(470, 420);
	closedSpr[SELECTED] = new Sprite("resources/GameScene/Refrigerator/Ref_Close_Activate.png");
	closedSpr[SELECTED]->SetEnabled(false);
	closedSpr[SELECTED]->position = Math::Vector(370, 320);
	openedSpr[SELECTED] = new Sprite("resources/GameScene/Refrigerator/Ref_Door_Activate.png");
	openedSpr[SELECTED]->SetEnabled(false);
	openedSpr[SELECTED]->position = Math::Vector(700, 410);

	Math::Vector caffeinePos[5] = { Math::Vector(525, 515), Math::Vector(595, 480), Math::Vector(615, 625), Math::Vector(560, 655), Math::Vector(505, 680) };

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			caffeine[i][j] = new Sprite("resources/GameScene/Drink/" + to_string(i) + "/" + to_string(j) + ".png");
			caffeine[i][j]->SetEnabled(false);
			caffeine[i][j]->position = caffeinePos[i] - Math::Vector(5, 5) * j;
		}
		caffeineInfo[i] = new Sprite("resources/GameScene/Info/" + to_string(i) + ".png");
		caffeineInfo[i]->SetEnabled(false);
		caffeineInfo[i]->position = Math::Vector(730, 570);
	}

	caffeineCost[LES_COFFEE] = 2;
	caffeineCost[MAX_COFFEE] = 4;
	caffeineCost[MON_DRINK] = 5;
	caffeineCost[RED_DRINK] = 3;
	caffeineCost[SIX_DRINK] = 1;

	canPos[0] = Math::Vector(350, 780);
	canPos[1] = Math::Vector(305, 800);
	canPos[2] = Math::Vector(380, 805);
	canHeight = 100;

	dopingSound = new Sound("audio/Doping.wav");
	openSound = new Sound("audio/open.wav");
	closeSound = new Sound("audio/close.wav");
}

void Refrigerator::ChangeState(bool state)
{
	if (!state)
		for (int i = 0; i < 5; i++)
			caffeineInfo[i]->SetEnabled(state);

	for (int i = 0; i < 5; i++)
		caffeine[i][NORMAL]->SetEnabled(state);

	openedSpr[NORMAL]->SetEnabled(state);
	closedSpr[NORMAL]->SetEnabled(!state);
}

void Refrigerator::OnUpdate()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	if (!isInit)
	{
		isInit = true;
		gameScene->PushBackGameObject(closedSpr[NORMAL]);
		gameScene->PushBackGameObject(openedSpr[NORMAL]);
		gameScene->PushBackGameObject(closedSpr[SELECTED]);
		gameScene->PushBackGameObject(openedSpr[SELECTED]);

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 2; j++)
				gameScene->PushBackGameObject(caffeine[i][j]);
		for (int i = 0; i < 5; i++)
			gameScene->PushBackGameObject(caffeineInfo[i]);
	}

	Math::Vector mousePos;
	RGInput->GetMouseFromClient(mousePos);

	if (closedSpr[NORMAL]->GetEnabled() && closedSpr[NORMAL]->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		closedSpr[SELECTED]->SetEnabled(true);
		if (RGInput->TriggerMouse(0))
		{
			openSound->audio->Play();
			ChangeState(true);
			return;
		}
	}
	else
		closedSpr[SELECTED]->SetEnabled(false);

	bool isMouseOnCaffeine = false;

	for (int i = 0; i < 5; i++)
		if (caffeine[i][NORMAL]->GetEnabled() && caffeine[i][NORMAL]->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos) && !gameScene->developer->isDead && !gameScene->isTropicanaTime)
		{
			isMouseOnCaffeine = true;
			caffeine[i][SELECTED]->SetEnabled(true);
			for (int j = 0; j < 5; j++)
				caffeineInfo[j]->SetEnabled(false);
			caffeineInfo[i]->SetEnabled(true);

			if (RGInput->TriggerMouse(0) && GameManager::GetInstance()->hasTearCount >= caffeineCost[i])
			{
				GameManager::GetInstance()->hasTearCount -= caffeineCost[i];
				dopingSound->audio->Play();

				if (i <= 1)
				{
					TextEffect *text = new TextEffect("resources/GameScene/Caffeine.png");
					text->position.SetVector(850, 370);
					gameScene->PushBackGameObject(text);
				}
				else
				{
					TextEffect *text = new TextEffect("resources/GameScene/Drink.png");
					text->position.SetVector(940, 440);
					gameScene->PushBackGameObject(text);
				}

				Sprite *can = new Sprite("resources/GameScene/Drink/" + to_string(i) + "/0.png");
				can->position = canPos[gameScene->canList.size() % 3] - Math::Vector(0, canHeight * (int)(gameScene->canList.size() / 3));
				gameScene->PushBackGameObject(can);
				gameScene->canList.push_back(can);

				if (i == LES_COFFEE)
					gameScene->developer->exhaustion /= 2;
				else if (i == MAX_COFFEE)
					gameScene->developer->exhaustion = 0;
				else if (i == SIX_DRINK)
					gameScene->developer->PlusHp(15);
				else if (i == RED_DRINK)
					gameScene->developer->PlusHp(50);
				else if (i == MON_DRINK)
					gameScene->developer->PlusHp(100);

				GameManager::GetInstance()->howDrinkCan++;
				if (GameManager::GetInstance()->howDrinkCan >= 18 && GameManager::GetInstance()->isFirstAddict)
				{
					gameScene->isFinish = true;
					gameScene->goToEndingType = ADDICT_ENDING;
				}
			}

			return;
		}
		else
			caffeine[i][SELECTED]->SetEnabled(false);

	if (!isMouseOnCaffeine && openedSpr[NORMAL]->GetEnabled() && openedSpr[NORMAL]->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		openedSpr[SELECTED]->SetEnabled(true);
		if (RGInput->TriggerMouse(0))
		{
			closeSound->audio->Play();
			ChangeState(false);
			return;
		}
	}
	else
		openedSpr[SELECTED]->SetEnabled(false);
}