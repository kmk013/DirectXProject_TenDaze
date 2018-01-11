#include "EndingScene.h"
#include "Sprite.h"
#include "GameManager.h"
#include "GameScene.h"
#include "MainScene.h"
#include <fstream>

using namespace RGEngine;

EndingScene::EndingScene(EndingType type)
{
	Sprite *endingBack = new Sprite("resources/Ending/Ending_BG.png");
	PushBackGameObject(endingBack);

	for (int i = 0; i < 4; i++)
	{
		if (i < 2)
			for (int j = 0; j < 10; j++)
			{
				tearText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
				tearText[i][j]->SetEnabled(false);
				tearText[i][j]->position = Math::Vector(1480, 670) + Math::Vector(50, 0) * i;
				PushBackGameObject(tearText[i][j]);

				drinkText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
				drinkText[i][j]->SetEnabled(false);
				drinkText[i][j]->position = Math::Vector(1520, 780) + Math::Vector(50, 0) * i;
				PushBackGameObject(drinkText[i][j]);
			}
		if (i < 3)
			for (int j = 0; j < 10; j++)
			{
				developText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
				developText[i][j]->SetEnabled(false);
				developText[i][j]->position = Math::Vector(1600, 340) + Math::Vector(50, 0) * i;
				PushBackGameObject(developText[i][j]);

				sleepText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
				sleepText[i][j]->SetEnabled(false);
				sleepText[i][j]->position = Math::Vector(1430, 560) + Math::Vector(50, 0) * i;
				PushBackGameObject(sleepText[i][j]);
			}

		for (int j = 0; j < 10; j++)
		{
			hitDeveloperText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
			hitDeveloperText[i][j]->SetEnabled(false);
			hitDeveloperText[i][j]->position = Math::Vector(1600, 450) + Math::Vector(50, 0) * i;
			PushBackGameObject(hitDeveloperText[i][j]);
		}
	}

	Sprite *ending = nullptr;
	if (type == ADDICT_ENDING)
	{
		GameManager::GetInstance()->isFirstAddict = false;
		ending = new Sprite("resources/Ending/addict.png");
	}
	if (type == BLUE_SCREEN_ENDING)
	{
		GameManager::GetInstance()->isFirstBlueScreen = false;
		ending = new Sprite("resources/Ending/BlueScreen.png");
	}
	if (type == CHICKEN_ENDING)
		ending = new Sprite("resources/Ending/Chicken.png");
	if (type == PC_ROOM_ENDING)
		ending = new Sprite("resources/Ending/PCroom.png");
	if (type == SLEEP_ENDING)
		ending = new Sprite("resources/Ending/DeepSleep.png");
	if (type == TROPICANA_ENDING)
	{
		GameManager::GetInstance()->isFirstTropicana = false;
		ending = new Sprite("resources/Ending/Sparkling.png");
	}
	ending->position.SetVector(140, 50);
	PushBackGameObject(ending);

	replayBtn = new Sprite("resources/Ending/PlayAgain.png");
	replayBtn->position.SetVector(1120, 910);
	PushBackGameObject(replayBtn);
	
	endingInfo = new Sprite("resources/Ending/" + to_string(type + 1) + ".png");
	endingInfo->position.SetVector(1090, 50);
	PushBackGameObject(endingInfo);

	continueBtn = new Sprite("resources/Ending/Continue.png");
	continueBtn->position.SetVector(1540, 910);
	PushBackGameObject(continueBtn);

	realBlackScreen = new Sprite("resources/BlackScreen.png");
	PushBackGameObject(realBlackScreen);

	replayBtn->scalingCenter = Math::Vector(replayBtn->sprite->GetTexture()->GetWidth(), replayBtn->sprite->GetTexture()->GetHeight()) / 2;
	continueBtn->scalingCenter = Math::Vector(continueBtn->sprite->GetTexture()->GetWidth(), continueBtn->sprite->GetTexture()->GetHeight()) / 2;

	endingBGM = new Sound("audio/endingScene.mp3");

	Save(type);

	cursor = new Sprite("resources/Whip/" + to_string(GameManager::GetInstance()->whipPower - 1) + ".png");
	PushBackGameObject(cursor);
}

void EndingScene::OnUpdate()
{
	if (!endingBGM->audio->IsPlaying())
		endingBGM->audio->Play();

	Math::Vector mousePos;
	RGInput->GetMouseFromClient(mousePos);

	cursor->position = mousePos;

	if (RGInput->Trigger(DIK_F1))
		Reset();

	int developT = (int)GameManager::GetInstance()->howDeveloped;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
			developText[2 - i][j]->SetEnabled(false);
		developText[2 - i][developT % 10]->SetEnabled(true);
		developT /= 10;
	}

	int hitDevelopT = GameManager::GetInstance()->howHitDeveloper > 9999 ? 9999 : GameManager::GetInstance()->howHitDeveloper;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
			hitDeveloperText[3 - i][j]->SetEnabled(false);
		hitDeveloperText[3 - i][hitDevelopT % 10]->SetEnabled(true);
		hitDevelopT /= 10;
	}

	int sleepT = (int)(GameManager::GetInstance()->sleepTime / 60);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
			sleepText[2 - i][j]->SetEnabled(false);
		sleepText[2 - i][sleepT % 10]->SetEnabled(true);
		sleepT /= 10;
	}

	int tearT = GameManager::GetInstance()->allTearCount > 99 ? 99 : GameManager::GetInstance()->allTearCount;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			tearText[1 - i][j]->SetEnabled(false);
		tearText[1 - i][tearT % 10]->SetEnabled(true);
		tearT /= 10;
	}

	int drinkT = GameManager::GetInstance()->howDrinkCan;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			drinkText[1 - i][j]->SetEnabled(false);
		drinkText[1 - i][drinkT % 10]->SetEnabled(true);
		drinkT /= 10;
	}

	if (realBlackScreen->sprite->GetTexture()->color.a > 0)
		realBlackScreen->sprite->GetTexture()->color.a -= RGEngine::deltaTime();

	if (replayBtn->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		replayBtn->scale = Math::Vector(1.2f, 1.2f);
		if (RGInput->TriggerMouse(0))
		{
			GameManager::GetInstance()->Reset();
			endingBGM->audio->Stop();
			RGApp->ChangeScene(new GameScene);
			return;
		}
	}
	else 
		replayBtn->scale = Math::Vector(1, 1);

	if (continueBtn->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		continueBtn->scale = Math::Vector(1.2f, 1.2f);
		if (RGInput->TriggerMouse(0))
		{
			GameManager::GetInstance()->Reset();
			endingBGM->audio->Stop();
			RGApp->ChangeScene(new MainScene);
			return;
		}
	}
	else
		continueBtn->scale = Math::Vector(1, 1);
}

void EndingScene::Save(EndingType type)
{
	int power = 0;
	GameManager::GetInstance()->endingOpened[type] = 1;
	ofstream outFile("resources/data.txt");
	for (int i = 0; i < 6; i++)
	{
		outFile.put(GameManager::GetInstance()->endingOpened[i] + '0');
		power += GameManager::GetInstance()->endingOpened[i];
	}outFile.close();
	GameManager::GetInstance()->whipPower = power + 1;
}

void EndingScene::Reset()
{
	for(int i = 0; i < 6; i++)
		GameManager::GetInstance()->endingOpened[i] = 0;
	ofstream outFile("resources/data.txt");
	for (int i = 0; i < 6; i++)
		outFile.put(GameManager::GetInstance()->endingOpened[i] + '0');
	outFile.close();
	GameManager::GetInstance()->whipPower = 1;
	GameManager::GetInstance()->isFirstBlueScreen = true;
	GameManager::GetInstance()->isFirstTropicana = true;
	GameManager::GetInstance()->isFirstAddict = true;
}

EndingScene::~EndingScene()
{
}
