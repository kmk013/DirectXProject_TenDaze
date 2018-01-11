#include "UI.h"
#include "GameManager.h"
#include "GameScene.h"

using namespace RGEngine;

UI::UI() : isInit(false)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			tearText[i][j] = new Sprite("resources/GameScene/TearNum/" + to_string(j) + ".png");
			tearText[i][j]->SetEnabled(false);
			tearText[i][j]->position = Math::Vector(570, 150) + Math::Vector(60, -30) * i;

			developText[i][j] = new Sprite("resources/GameScene/DevelopNum/" + to_string(j) + ".png");
			developText[i][j]->SetEnabled(false);
			developText[i][j]->position = Math::Vector(1780, 980) + Math::Vector(50, 0) * i;
		}
	}

	blackScreen = new Sprite("resources/GameScene/NextDay/BlackScreen.png");
	blackScreen->sprite->GetTexture()->color.a = 0;

	tropScreen = new Animation();
	tropScreen->ani->PushBackFrame("resources/GameScene/Sparkling/Red.png");
	tropScreen->ani->PushBackFrame("resources/GameScene/Sparkling/Green.png");
	tropScreen->ani->PushBackFrame("resources/GameScene/Sparkling/Blue.png");
	tropScreen->SetEnabled(false);

	for (int i = 0; i < 10; i++)
	{
		nextDay[i] = new Sprite("resources/GameScene/NextDay/" + to_string(i) + ".png");
		nextDay[i]->sprite->GetTexture()->color.a = 0;
		nextDay[i]->position.SetVector(880, 480);
	}

	realBlackScreen = new Sprite("resources/BlackScreen.png");
	realBlackScreen->sprite->GetTexture()->color.a = 0;
}

void UI::OnUpdate()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	tropScreen->ani->speed = gameScene->tropicanaSpeed;

	if (!isInit)
	{
		isInit = true;

		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 10; j++)
			{
				gameScene->PushBackGameObject(tearText[i][j]);
				gameScene->PushBackGameObject(developText[i][j]);
			}

		gameScene->PushBackGameObject(blackScreen);
		for(int i = 0; i < 10; i++)
			gameScene->PushBackGameObject(nextDay[i]);

		gameScene->PushBackGameObject(tropScreen);

		gameScene->PushBackGameObject(realBlackScreen);
	}


	int tearT = GameManager::GetInstance()->hasTearCount;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			tearText[1 - i][j]->SetEnabled(false);
		tearText[1 - i][tearT % 10]->SetEnabled(true);
		tearT /= 10;
	}

	if((int)GameManager::GetInstance()->howDeveloped >= 100)
	{
		gameScene->isFinish = true;
		gameScene->goToEndingType = CHICKEN_ENDING;
	}

	int developT = (int)GameManager::GetInstance()->howDeveloped > 99 ? 99 : (int)GameManager::GetInstance()->howDeveloped;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			developText[1 - i][j]->SetEnabled(false);
		developText[1 - i][developT % 10]->SetEnabled(true);
		developT /= 10;
	}
}