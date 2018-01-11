#include "Timer.h"

#include "RGEngine.h"
#include "GameManager.h"
#include "GameScene.h"

Timer::Timer() : checker(0.0f), hour(22), minute(0), day(1), isSleep(false), isInit(false), isDayVisible(false), isDayFadein(true), blueScreenTimer(0)
{
	for (int i = 0; i < 11; i++)
	{
		calendar[i] = new Sprite("resources/GameScene/Calender/" + to_string(i) + ".png");
		calendar[i]->SetEnabled(false);
		calendar[i]->position.SetVector(110, 380);
	} calendar[1]->SetEnabled(true);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			hourText[i][j] = new Sprite("resources/GameScene/ClockNum/" + to_string(j) + ".png");
			hourText[i][j]->SetEnabled(false);
			hourText[i][j]->position = Math::Vector(110, 240) + Math::Vector(60, -30) * i;

			minuteText[i][j] = new Sprite("resources/GameScene/ClockNum/" + to_string(j) + ".png");
			minuteText[i][j]->SetEnabled(false);
			minuteText[i][j]->position = Math::Vector(270, 160) + Math::Vector(60, -30) * i;
		}
	}

	wakeUpSound = new Sound("audio/fin.m4a");
}

Timer::~Timer()
{
}

void Timer::InitTimer()
{
	isInit = true;
	RGEngine::Scene *gameScene = RGApp->GetScene();
	for (int i = 0; i < 11; i++)
		gameScene->PushBackGameObject(calendar[i]);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 10; j++)
		{
			gameScene->PushBackGameObject(hourText[i][j]);
			gameScene->PushBackGameObject(minuteText[i][j]);
		}
}

void Timer::OnUpdate()
{
	if (!isInit)
		InitTimer();

	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	if (!gameScene->developer->isDead) {
		TimeCountOnAwake();
	}
	else {
		TimeCountOnSleep();
	}

	WatchUpdate();

	//게임 종료
	if (day == 10 && hour >= 16) {
		OnEnd();
	}
}

void Timer::OnEnd()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();
	
	gameScene->isFinish = true;
	if(GameManager::GetInstance()->howDeveloped < 60)
		gameScene->goToEndingType = SLEEP_ENDING;
	if (GameManager::GetInstance()->howDeveloped >= 60)
		gameScene->goToEndingType = PC_ROOM_ENDING;
}

void Timer::TimeCountOnAwake()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();
	
	checker += RGEngine::deltaTime();
	
	ShowDayText();

	if (!gameScene->isBlueScreen)
		GameManager::GetInstance()->howDeveloped += RGEngine::deltaTime() * 0.2f;

	if (checker >= 0.05f) {
		checker -= 0.05f;

		if (!gameScene->isTropicanaTime)
		{
			++minute;
			++blueScreenTimer;
			if (Math::Random(1, 10000) == 1 && !gameScene->isBlueScreen && hour != 3 && hour != 4)
			{
				gameScene->isBlueScreen = true;
				blueScreenTimer = 0;
				int rollBack = Math::Random(5, 10);
				GameManager::GetInstance()->howDeveloped = GameManager::GetInstance()->howDeveloped - rollBack < 0 ? 0 : GameManager::GetInstance()->howDeveloped - rollBack;
				if (GameManager::GetInstance()->isFirstBlueScreen)
					GameManager::GetInstance()->howDeveloped = 0;
				
				gameScene->developer->ChangeAnimation(BLUE_SCREEN);
			}

			if (gameScene->isBlueScreen && blueScreenTimer >= 60)
			{
				if (GameManager::GetInstance()->isFirstBlueScreen)
				{
					gameScene->isFinish = true;
					gameScene->goToEndingType = BLUE_SCREEN_ENDING;
					gameScene->mainBGM->audio->Stop();
					return;
				}
				else
				{
					gameScene->mainBGM->audio->Play();
					gameScene->isBlueScreen = false;
					gameScene->developer->ChangeAnimation(TROEND);
				}
			}
		}
	}
	if (minute >= 60) {
		minute = 0;
		++hour;
	}
	if (hour == 4) {
		gameScene->developer->isDead = true;
		gameScene->developer->ChangeAnimation(SLEEP);
	}
	else if (hour >= 24) {
		hour = 0;
		++day;
		CalendarUpdate();
	}
}

void Timer::TimeCountOnSleep()
{
	//잘때
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	minute++;
	GameManager::GetInstance()->sleepTime++;

	if (minute >= 60) {
		minute = 0;
		++hour;
	}
	if (hour >= 24) {
		hour = 0;
		++day;
		CalendarUpdate();
	}
	if (hour == 5 && minute >= 10)
		ShowBlackScreen(false);
	else
		ShowBlackScreen(true);
	if (hour == 6&&minute==0) {
		gameScene->developer->isDead = false;
		//체력 회복시키기
		gameScene->developer->exhaustion = 0;
		gameScene->developer->hp = gameScene->developer->maxHp;
		gameScene->developer->ChangeAnimation(NORMAL_1);

		isDayVisible = true;
		wakeUpSound->audio->Play();
	}
}

void Timer::ShowBlackScreen(bool fadein)
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	static float a;
	if (fadein) {
		a += 0.02f;
		if (a > 1.0f)
			a = 1.0f;
	}
	else {
		a -= 0.02f;
		if (a < 0.0f)
			a = 0.0f;
	}
	gameScene->ui->blackScreen->sprite->GetTexture()->color.a = a;
}

void Timer::ShowDayText()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	static float a;
	static bool waiting;
	static float waittimer;
	if (isDayVisible) {
		if (isDayFadein) {
			a += RGEngine::deltaTime();
			gameScene->ui->nextDay[day - 1]->SetEnabled(true);
			gameScene->ui->nextDay[day - 1]->sprite->GetTexture()->color.a = a;
			if (a >= 1.0f) {
				a = 1.0f;
				isDayFadein = false;
				waiting = true;
			}
		}
		else if (waiting) {
			waittimer += RGEngine::deltaTime();
			if (waittimer >= 2.0f) {
				waiting = false;
				waittimer = 0.0f;
			}
		}
		else {
			a -= RGEngine::deltaTime();
			gameScene->ui->nextDay[day - 1]->sprite->GetTexture()->color.a = a;
			if (a <= 0.0f)	{
				a = 0.0f;
				isDayVisible = false;
				gameScene->ui->nextDay[day - 1]->SetEnabled(false);
				isDayFadein = true;
			}
		}
	}
}

void Timer::CalendarUpdate()
{
	calendar[day - 1]->SetEnabled(false);
	calendar[day - 0]->SetEnabled(true);
}

void Timer::WatchUpdate()
{
	int minuteT = minute;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			minuteText[1 - i][j]->SetEnabled(false);
		minuteText[1 - i][minuteT % 10]->SetEnabled(true);
		minuteT /= 10;
	}

	int hourT = hour;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
			hourText[1 - i][j]->SetEnabled(false);
		hourText[1 - i][hourT % 10]->SetEnabled(true);
		hourT /= 10;
	}
}