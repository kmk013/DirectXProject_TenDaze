#include "GameScene.h"
#include "Tear.h"
#include "EndingScene.h"

GameScene::GameScene() : tropicanaTimer(0, 15), isTropicanaTime(false), tropicanaSpeed(3), isAutoClick(false), isFinish(false), initC(false), timerC(0)
{
	Sprite *gameBackground = new Sprite("resources/GameScene/BackGroud_Large.png");
	gameBackground->position.SetVector(-50, -50);
	PushBackGameObject(gameBackground);

	hpBar = new HpBar();
	PushBackGameObject(hpBar);

	refrigerator = new Refrigerator();
	PushBackGameObject(refrigerator);

	developer = new Developer();
	PushBackGameObject(developer);

	myTimer = new Timer();
	PushBackGameObject(myTimer);

	ui = new UI;
	PushBackGameObject(ui);

	cursor = new Sprite("resources/Whip/" + to_string(GameManager::GetInstance()->whipPower - 1) + ".png");

	mainBGM = new Sound("audio/main.mp3");
	tropicanaBGM = new Sound("audio/tropicana.mp3");
}

GameScene::~GameScene()
{
}

void GameScene::OnUpdate() 
{
	if (!initC && timerC > 0.1)
	{
		initC = true;
		PushBackGameObject(cursor);
	}
	timerC += RGEngine::deltaTime();

	RGInput->GetMouseFromClient(cursor->position);

	if (!mainBGM->audio->IsPlaying() && !isBlueScreen && !isTropicanaTime)
	{
		if (myTimer->day >= 5)
		{
			mainBGM->audio->Reset();
			mainBGM->audio->SetSound("audio/AfterBGM.mp3");
		}
		mainBGM->audio->Play();
	}
	GetCamera()->position += (-Math::Vector(0, 0) - GetCamera()->position) * 0.15;

	if (isFinish)
	{
		ui->realBlackScreen->sprite->GetTexture()->color.a += RGEngine::deltaTime();
		if (ui->realBlackScreen->sprite->GetTexture()->color.a > 1)
		{
			mainBGM->audio->Stop();
			RGApp->ChangeScene(new EndingScene(goToEndingType));
			return;
		}
	}

	if (isTropicanaTime)
	{
		tropicanaTimer.first += RGEngine::deltaTime();

		if (tropicanaTimer.first > tropicanaTimer.second) {
			if (GameManager::GetInstance()->isFirstTropicana)
			{
				isFinish = true;
				goToEndingType = TROPICANA_ENDING;
				return;
			}
			else
			{
				if(myTimer->day)
				mainBGM->audio->Play();
				tropicanaBGM->audio->Stop();

				tropicanaTimer.first = 0;

				isTropicanaTime = false;

				developer->ChangeAnimation(TROEND);
				ui->tropScreen->SetEnabled(false);
				hpBar->tropicanaBar->SetEnabled(false);
			}
		}
	}
	
	if (RGInput->Trigger(DIK_F1))
	{
		if (!isAutoClick)
			isAutoClick = true;
		else
			isAutoClick = false;
	}
	if (RGInput->Trigger(DIK_F2))
	{
		GameManager::GetInstance()->hasTearCount = 99;
	}
	if (RGInput->Trigger(DIK_F3) && !isBlueScreen && !isTropicanaTime)
	{
		Tear* t = new Tear(true);
		t->position.x = (float)RGEngine::Math::Random(0, 1920 - t->mys->GetTexture()->GetWidth());
		t->speed = (float)RGEngine::Math::Random(250, 800);
		RGApp->GetScene()->PushBackGameObject(t);
	}
	if (RGInput->Trigger(DIK_F4) && !isBlueScreen && !isTropicanaTime)
	{
		isBlueScreen = true;
		myTimer->blueScreenTimer = 0;
		int rollBack = Math::Random(5, 10);
		GameManager::GetInstance()->howDeveloped = GameManager::GetInstance()->howDeveloped - rollBack < 0 ? 0 : GameManager::GetInstance()->howDeveloped - rollBack;
		developer->ChangeAnimation(BLUE_SCREEN);
	}
	if (RGInput->Trigger(DIK_F5))
	{
		GameManager::GetInstance()->howDeveloped = GameManager::GetInstance()->howDeveloped + 10 > 100 ? 100 : GameManager::GetInstance()->howDeveloped + 10;
	}
	if (RGInput->Trigger(DIK_F6))
	{
		if(myTimer->day < 9)
			myTimer->day++;
	}
}