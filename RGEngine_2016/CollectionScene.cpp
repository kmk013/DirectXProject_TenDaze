#include "CollectionScene.h"
#include "GameManager.h"
#include "MainScene.h"

using namespace RGEngine;

CollectionScene::CollectionScene() : selectIndex(-1)
{
	collectionBack[0] = new Sprite("resources/Collection/Ending/Ending_BG.png");
	PushBackGameObject(collectionBack[0]);
	collectionBack[1] = new Sprite("resources/Collection/Whip/Whip_BG.png");
	PushBackGameObject(collectionBack[1]);
	collectionBack[1]->SetEnabled(false);

	backBtn = new Sprite("resources/Collection/Back.png");
	backBtn->position.SetVector(45, 45);
	PushBackGameObject(backBtn);

	nextBtn = new Sprite("resources/Collection/Ending/Next.png");
	nextBtn->position.SetVector(760, 205);
	PushBackGameObject(nextBtn);

	privBtn = new Sprite("resources/Collection/Whip/Prev.png");
	privBtn->position.SetVector(295, 205);
	PushBackGameObject(privBtn);
	privBtn->SetEnabled(false);

	backBtn->scalingCenter = Math::Vector(backBtn->sprite->GetTexture()->GetWidth(), backBtn->sprite->GetTexture()->GetHeight()) / 2;
	nextBtn->scalingCenter = Math::Vector(nextBtn->sprite->GetTexture()->GetWidth(), nextBtn->sprite->GetTexture()->GetHeight()) / 2;
	privBtn->scalingCenter = Math::Vector(privBtn->sprite->GetTexture()->GetWidth(), privBtn->sprite->GetTexture()->GetHeight()) / 2;

	activeImg = new Sprite("resources/Collection/Activate.png");
	activeImg->position.SetVector(-500, -500);
	PushBackGameObject(activeImg);

	Math::Vector smallPos[6] = { Math::Vector(140, 410), Math::Vector(410, 410), Math::Vector(680, 410),Math::Vector(140, 740),Math::Vector(410, 740),Math::Vector(680, 740) };

	for (int i = 0; i < 6; i++)
	{
		smallEnding[i] = new Sprite("resources/Collection/Ending/S_" + to_string(i + 1) + ".png");
		smallEnding[i]->position = smallPos[i];
		PushBackGameObject(smallEnding[i]);
		if (GameManager::GetInstance()->endingOpened[i] == 0)
			smallEnding[i]->SetEnabled(false);

		bigEnding[i] = new Sprite("resources/Collection/Ending/B_" + to_string(i + 1) + ".png");
		bigEnding[i]->position = Math::Vector(1090, 60);
		PushBackGameObject(bigEnding[i]);
		bigEnding[i]->SetEnabled(false);

		endingInfo[i] = new Sprite("resources/Collection/Ending/" + to_string(i + 1) + ".png");
		endingInfo[i]->position = Math::Vector(1090, 850);
		PushBackGameObject(endingInfo[i]);
		endingInfo[i]->SetEnabled(false);

		smallWhip[i] = new Sprite("resources/Collection/Whip/S_" + to_string(i + 1) + ".png");
		smallWhip[i]->position = smallPos[i];
		PushBackGameObject(smallWhip[i]);
		smallWhip[i]->SetEnabled(false);

		bigWhip[i] = new Sprite("resources/Collection/Whip/B_" + to_string(i + 1) + ".png");
		bigWhip[i]->position = Math::Vector(1090, 60);
		PushBackGameObject(bigWhip[i]);
		bigWhip[i]->SetEnabled(false);

		whipInfo[i] = new Sprite("resources/Collection/Whip/" + to_string(i + 1) + ".png");
		whipInfo[i]->position = Math::Vector(1090, 850);
		PushBackGameObject(whipInfo[i]);
		whipInfo[i]->SetEnabled(false);
	}

	cursor = new Sprite("resources/Whip/" + to_string(GameManager::GetInstance()->whipPower - 1) + ".png");
	PushBackGameObject(cursor);

	buttonSound = new Sound("audio/Button.wav");
	collectionBGM = new Sound("audio/collection.mp3");
}

void CollectionScene::OnUpdate()
{
	if (!collectionBGM->audio->IsPlaying())
	{
		collectionBGM->audio->Play();
		collectionBGM->audio->SetVolume(0.6f);
	}

	Math::Vector mousePos;
	RGInput->GetMouseFromClient(mousePos);

	cursor->position = mousePos;

	for (int i = 0; i < 6; i++)
	{
		if (smallEnding[i]->GetEnabled() && smallEnding[i]->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
		{
			activeImg->position.SetVector(smallEnding[i]->position - Math::Vector(5, 5));

			if (RGInput->TriggerMouse(0))
			{
				buttonSound->audio->Play();
				selectIndex = i;
				for (int j = 0; j < 6; j++)
				{
					bigEnding[j]->SetEnabled(false);
					endingInfo[j]->SetEnabled(false);
				}
				bigEnding[selectIndex]->SetEnabled(true);
				endingInfo[selectIndex]->SetEnabled(true);
			}
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (smallWhip[i]->GetEnabled() && smallWhip[i]->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
		{
			activeImg->position.SetVector(smallWhip[i]->position - Math::Vector(5, 5));

			if (RGInput->TriggerMouse(0))
			{
				buttonSound->audio->Play();
				selectIndex = i;
				for (int j = 0; j < 6; j++)
				{
					bigWhip[j]->SetEnabled(false);
					whipInfo[j]->SetEnabled(false);
				}
				bigWhip[selectIndex]->SetEnabled(true);
				whipInfo[selectIndex]->SetEnabled(true);
			}
		}
	}

	if (backBtn->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		backBtn->scale = Math::Vector(1.2f, 1.2f);
		if (RGInput->TriggerMouse(0))
		{
			buttonSound->audio->Play();
			collectionBGM->audio->Stop();
			RGApp->ChangeScene(new MainScene);
			return;
		}
	}
	else
		backBtn->scale = Math::Vector(1, 1);

	if (nextBtn->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		nextBtn->scale = Math::Vector(1.2f, 1.2f);
		if (RGInput->TriggerMouse(0))
		{
			buttonSound->audio->Play();

			for(int i = 0; i < GameManager::GetInstance()->whipPower - 1; i++)
				smallWhip[i]->SetEnabled(true);

			for (int i = 0; i < 6; i++)
			{
				smallEnding[i]->SetEnabled(false);
				bigEnding[i]->SetEnabled(false);
				endingInfo[i]->SetEnabled(false);
			}
			selectIndex = -1;
			activeImg->position.SetVector(-500, -500);

			nextBtn->SetEnabled(false);
			privBtn->SetEnabled(true);
			collectionBack[0]->SetEnabled(false);
			collectionBack[1]->SetEnabled(true);
			return;
		}
	}
	else
		nextBtn->scale = Math::Vector(1, 1);

	if (privBtn->GetComponent<Components::BoxCollider>()->GetBoxWithPosition().Intersected(mousePos))
	{
		privBtn->scale = Math::Vector(1.2f, 1.2f);
		if (RGInput->TriggerMouse(0))
		{
			for (int i = 0; i < 6; i++)
			{
				if (GameManager::GetInstance()->endingOpened[i] == 1)
					smallEnding[i]->SetEnabled(true);
				smallWhip[i]->SetEnabled(false);
				bigWhip[i]->SetEnabled(false);
				whipInfo[i]->SetEnabled(false);
			}

			buttonSound->audio->Play();
			nextBtn->SetEnabled(true);
			privBtn->SetEnabled(false);
			collectionBack[0]->SetEnabled(true);
			collectionBack[1]->SetEnabled(false);
			return;
		}
	}
	else
		privBtn->scale = Math::Vector(1, 1);
}

CollectionScene::~CollectionScene()
{

}
