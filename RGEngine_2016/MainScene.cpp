#include "MainScene.h"
#include "Sprite.h"
#include "GameScene.h"
#include "CollectionScene.h"
#include "GameManager.h"

using namespace RGEngine;

MainScene::MainScene() : howToCnt(-1)
{
	Sprite *gameBackground = new Sprite("resources/MainScene/BackGround.png");
	gameBackground->position.SetVector(0, 0);
	PushBackGameObject(gameBackground);

	title = new Sprite("resources/MainScene/Title.png");
	title->position.SetVector(45, 110);
	PushBackGameObject(title);

	gameStart = new Sprite("resources/MainScene/GameStart.png");
	gameStart->position.SetVector(45, 540);
	gameStart->scalingCenter.x = gameStart->sprite->GetTexture()->GetWidth() * 0.5f;
	gameStart->scalingCenter.y = gameStart->sprite->GetTexture()->GetHeight() * 0.5f;
	PushBackGameObject(gameStart);

	howToPlay = new Sprite("resources/MainScene/HowToPlay.png");
	howToPlay->position.SetVector(45, 710);
	howToPlay->scalingCenter.x = howToPlay->sprite->GetTexture()->GetWidth() * 0.5f;
	howToPlay->scalingCenter.y = howToPlay->sprite->GetTexture()->GetHeight() * 0.5f;
	PushBackGameObject(howToPlay);

	collection = new Sprite("resources/MainScene/Collection.png");
	collection->position.SetVector(45, 880);
	collection->scalingCenter.x = collection->sprite->GetTexture()->GetWidth()*0.5f;
	collection->scalingCenter.y = collection->sprite->GetTexture()->GetHeight()*0.5f;
	PushBackGameObject(collection);

	exitButton = new Sprite("resources/MainScene/Exit.png");
	exitButton->position.SetVector(1660, 945);
	exitButton->scalingCenter.x = exitButton->sprite->GetTexture()->GetWidth()*0.5f;
	exitButton->scalingCenter.y = exitButton->sprite->GetTexture()->GetHeight()*0.5f;
	PushBackGameObject(exitButton);

	buttonSound = new Sound("audio/Button.wav");
	mainBGM = new Sound("audio/MainSceneBGM.mp3");

	for (int i = 0; i < 3; i++)
	{
		PushBackGameObject(howToEx[i] = new Sprite("resources/HowtoPlay/" + to_string(i + 1) + ".png"));
		howToEx[i]->SetEnabled(false);
	}

	cursor = new Sprite("resources/Whip/" + to_string(GameManager::GetInstance()->whipPower - 1) + ".png");
	PushBackGameObject(cursor);

	ShowCursor(false);
}
void MainScene::OnUpdate()
{
	if (!mainBGM->audio->IsPlaying())
		mainBGM->audio->Play();

	Math::Vector mousePos;
	RGInput->GetMouseFromClient(mousePos);

	cursor->position = mousePos;

	if (gameStart->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
		gameStart->scale.x = 1.1f;
		gameStart->scale.y = 1.1f;
	}
	else {
		gameStart->scale.x = 1.0f;
		gameStart->scale.y = 1.0f;
	}
	if (howToPlay->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
		howToPlay->scale.x = 1.1f;
		howToPlay->scale.y = 1.1f;
	}
	else {
		howToPlay->scale.x = 1.0f;
		howToPlay->scale.y = 1.0f;
	}
	if (collection->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
		collection->scale.x = 1.1f;
		collection->scale.y = 1.1f;
	}
	else {
		collection->scale.x = 1.0f;
		collection->scale.y = 1.0f;
	}
	if (exitButton->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
		exitButton->scale.x = 1.1f;
		exitButton->scale.y = 1.1f;
	}
	else {
		exitButton->scale.x = 1.0f;
		exitButton->scale.y = 1.0f;
	}

	if (RGInput->TriggerMouse(0)) {
		if (howToCnt == 2)
		{
			buttonSound->audio->Play();
			howToEx[howToCnt]->SetEnabled(false);
			howToCnt = -1;
			return;
		}
		else if (howToCnt >= 0)
		{
			buttonSound->audio->Play();
			howToEx[howToCnt]->SetEnabled(false);
			howToEx[++howToCnt]->SetEnabled(true);
			return;
		}
		else
		{
			if (gameStart->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
				mainBGM->audio->Stop();
				buttonSound->audio->Play();
				RGApp->ChangeScene(new GameScene());
				return;
			}
			else if (howToPlay->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
				howToCnt = 0;
				howToEx[howToCnt]->SetEnabled(true);
				buttonSound->audio->Play();
				return;
			}
			else if (collection->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
				mainBGM->audio->Stop();
				buttonSound->audio->Play();
				RGApp->ChangeScene(new CollectionScene());
				return;
			}
			else if (exitButton->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos)) {
				buttonSound->audio->Play();
				exit(0);
			}
		}
	}
}

MainScene::~MainScene()
{

}
