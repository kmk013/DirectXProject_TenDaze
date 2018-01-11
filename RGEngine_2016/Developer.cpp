#include "Developer.h"
#include "Tear.h"
#include "GameManager.h"
#include "WhipEffect.h"
#include "GameScene.h"

using namespace RGEngine;

Developer::Developer() : exhaustion(0), hp(100), maxHp(100), isInit(false), isDead(false)
{
	developerAni = new Animation();
	developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_1.png");
	developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_2.png");
	developerAni->SetCollider();
	developerAni->ani->speed = 1.5f;
	developerAni->position.SetVector(880, 250);

	monitorAni = new Animation();
	for (int i = 0; i < 18; i++)
		monitorAni->ani->PushBackFrame("resources/GameScene/ComputerScreen/" + to_string(i) + ".png");
	monitorAni->ani->speed = 4;
	monitorAni->position.SetVector(850, 150);

	lastHp = hp;

	whipSound = new Sound("audio/whipSound.mp3");
	deathSound = new Sound("audio/Peok.wav");
	blueScreenSound = new Sound("audio/blueScreen.wav");
}

void Developer::ChangeAnimation(PlayerState state)
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();
	developerAni->ani->Reset();

	if (state == SLEEP) {
		deathSound->audio->Play();
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Down.png");
		monitorAni->ani->Stop();
	}
	else if (state == NORMAL_1)
	{
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_1.png");
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_2.png");
		monitorAni->ani->pause = false;
		developerAni->ani->speed = 1.5f;
	}
	else if (state == NORMAL_2)
	{
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Second_1.png");
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Second_2.png");
		monitorAni->ani->pause = false;
		developerAni->ani->speed = 1.5f;
	}
	else if (state == NORMAL_3)
	{
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Third_1.png");
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Third_2.png");
		monitorAni->ani->pause = false;
		developerAni->ani->speed = 1.5f;
	}
	else if (state == TROPICANA)
	{
		developerAni->ani->PushBackFrame("resources/GameScene/Sparkling/Slave_1.png");
		developerAni->ani->PushBackFrame("resources/GameScene/Sparkling/Slave_2.png");
		developerAni->ani->speed = gameScene->tropicanaSpeed;
		monitorAni->ani->Reset();
		monitorAni->ani->pause = false;
		monitorAni->ani->PushBackFrame("resources/GameScene/Sparkling/Screen_Red.png");
		monitorAni->ani->PushBackFrame("resources/GameScene/Sparkling/Screen_Green.png");
		monitorAni->ani->PushBackFrame("resources/GameScene/Sparkling/Screen_Blue.png");
		monitorAni->ani->speed = gameScene->tropicanaSpeed;
	}
	else if (state == TROEND) {
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_1.png");
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_First_2.png");
		developerAni->ani->speed = 1.5f;
		MonitorReset();
	}
	else if (state == BLUE_SCREEN) {
		gameScene->mainBGM->audio->Pause();
		blueScreenSound->audio->Play();
		developerAni->ani->PushBackFrame("resources/GameScene/Slave/Slave_Down.png");
		monitorAni->ani->Reset();
		monitorAni->ani->PushBackFrame("resources/GameScene/ComputerScreen/blue.png");
	}
}

void Developer::MonitorReset()
{
	monitorAni->ani->Reset();
	for (int i = 0; i < 18; i++)
		monitorAni->ani->PushBackFrame("resources/GameScene/ComputerScreen/" + to_string(i) + ".png");
	monitorAni->ani->speed = 4;
}

void Developer::OnUpdate()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	if (!isInit)
	{
		isInit = true;

		gameScene->PushBackGameObject(monitorAni);
		gameScene->PushBackGameObject(developerAni);
	}

	if (!isDead && !gameScene->isTropicanaTime && !gameScene->isBlueScreen)
		hp -= exhaustion += 0.01f * RGEngine::deltaTime();


	//¸ÂÀº°Å ÆÇÁ¤
	if (RGInput->TriggerMouse(0))
	{
		Math::Vector mousePos;
		RGInput->GetMouseFromClient(mousePos);

		if (developerAni->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos) && !isDead && !gameScene->isTropicanaTime)
		{
			Hit();
			whipSound->audio->Play();
			GameManager::GetInstance()->howHitDeveloper++;
			gameScene->GetCamera()->position.SetVector(Math::Random(-15, 15), Math::Random(-15, 15));
			WhipEffect *effect = new WhipEffect(mousePos, "resources/GameScene/Particle/" + to_string(GameManager::GetInstance()->whipPower - 1) + ".png", 2);
			gameScene->PushBackGameObject(effect);
		}
	}

	if(gameScene->isAutoClick)
		Hit();

	if (hp <= 0) {
		hp = -1;
		exhaustion = 0;
		isDead = true;
		ChangeAnimation(SLEEP);
	}

	if (!isDead && !gameScene->isTropicanaTime) {
		if (maxHp * 0.6 <= hp && maxHp * 0.6 > lastHp) {
			ChangeAnimation(NORMAL_1);
		}
		else if (maxHp * 0.6 > hp && maxHp * 0.3 < hp
			&& (maxHp * 0.6 <= lastHp || maxHp * 0.3 >= lastHp)) {
			ChangeAnimation(NORMAL_2);
		}
		else if (maxHp * 0.3 > hp && maxHp * 0.3 <= lastHp) {
			ChangeAnimation(NORMAL_3);
		}
		lastHp = hp;
	}
}

void Developer::Hit()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();
	//Ã¼·Â 
	PlusHp(GameManager::GetInstance()->whipPower);
	
	//·£´ýÀ¸·Î ´«¹°¶³±À
	int r = RGEngine::Math::Random(1, 100);
	if (r == 50)
	{
		int r2 = RGEngine::Math::Random(1, 100);
		if (r2 == 50 && !gameScene->isTropicanaTime && !gameScene->isBlueScreen)
		{
			//Æ®·ÎÇÇÄ«³ª
			Tear* t = new Tear(true);
			t->position.x = (float)RGEngine::Math::Random(1, 1920 - t->mys->GetTexture()->GetWidth());
			t->speed = (float)RGEngine::Math::Random(250, 600);
			RGApp->GetScene()->PushBackGameObject(t);
		}
		else
		{
			//´«¹° ¶³±À
			Tear* t = new Tear(false);
			t->position.x = (float)RGEngine::Math::Random(1, 1920 - t->mys->GetTexture()->GetWidth());
			t->speed = (float)RGEngine::Math::Random(250, 600);
			RGApp->GetScene()->PushBackGameObject(t);
		}
	}
}

void Developer::PlusHp(int amount)
{
	hp = hp + amount > maxHp ? maxHp : hp + amount;
}