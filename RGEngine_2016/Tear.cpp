#include "Tear.h"
#include "GameManager.h"
#include "GameScene.h"
#include "TextEffect.h"

Tear::Tear(bool isSpark) : isSparkling(isSpark)
{
	name = "tear";

	if (!isSparkling) {
		mys = AttachComponent<Components::SpriteRenderer>();
		mys->SetTexture("resources/GameScene/Tear.png");
		auto col = AttachComponent<Components::BoxCollider>();
		col->box.SetRect(0.0f, 0.0f, (float)mys->GetTexture()->GetWidth(), (float)mys->GetTexture()->GetHeight());
	}
	else {
		mys = AttachComponent<Components::SpriteRenderer>();
		mys->SetTexture("resources/GameScene/Sparkling/Spa.png");
		auto col = AttachComponent<Components::BoxCollider>();
		col->box.SetRect(0.0f, 0.0f, (float)mys->GetTexture()->GetWidth(), (float)mys->GetTexture()->GetHeight());
	}

	getTearSound = new Sound("audio/getTear.mp3");
}

Tear::~Tear()
{
}

void Tear::OnUpdate()
{
	position.y += speed*RGEngine::deltaTime();
	Math::Vector mousePos;
	RGInput->GetMouseFromClient(mousePos);

	if (GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		if (RGInput->TriggerMouse(0))
		{
			if (isSparkling)
				Sagwatoktoktok();
			else
				TearGain();
		}
	}

	if (position.y >= 1100.0f)
		Destroy();
}

void Tear::TearGain()
{
	if(GameManager::GetInstance()->hasTearCount < 99)
		GameManager::GetInstance()->hasTearCount++;
	
	if (GameManager::GetInstance()->allTearCount < 99)
		GameManager::GetInstance()->allTearCount++;

	getTearSound->audio->Play();

	Destroy();
}

void Tear::Sagwatoktoktok()
{
	GameScene *gameScene = (GameScene*)RGApp->GetScene();

	gameScene->mainBGM->audio->Stop();
	gameScene->tropicanaBGM->audio->Play();
	gameScene->tropicanaBGM->audio->SetVolume(0.7f);

	gameScene->isTropicanaTime = true;
	gameScene->developer->ChangeAnimation(TROPICANA);
	gameScene->developer->hp = gameScene->developer->maxHp;
	gameScene->developer->developerAni->ani->speed = gameScene->tropicanaSpeed;
	
	gameScene->developer->monitorAni->ani->speed = gameScene->tropicanaSpeed;

	gameScene->ui->tropScreen->SetEnabled(true);
	gameScene->ui->tropScreen->ani->Stop();
	gameScene->ui->tropScreen->ani->pause = false;
	gameScene->ui->tropScreen->ani->speed = gameScene->tropicanaSpeed;
	gameScene->hpBar->tropicanaBar->SetEnabled(true);

	TextEffect *text = new TextEffect("resources/GameScene/Sparkling/Sparkling.png");
	text->position.SetVector(830, 340);
	gameScene->PushBackGameObject(text);
	Destroy();

}
