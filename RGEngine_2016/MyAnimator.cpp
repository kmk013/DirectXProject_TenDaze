#include "MyAnimator.h"

MyAnimator::MyAnimator()
{
	animator = AttachComponent<Components::AnimationRenderer>();
	animator->speed = 10;
	moveAngle = 0;
}

MyAnimator::MyAnimator(std::string path)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);
	sprite->GetGameObject()->rotationCenter.SetVector(
		sprite->GetTexture()->GetWidth() / 2.0f,
		sprite->GetTexture()->GetWidth() / 2.0f);

	moveAngle = 0;
}

MyAnimator::~MyAnimator()
{
}

void MyAnimator::InitImage(std::string path)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);

	sprite->GetGameObject()->rotationCenter.SetVector(
		sprite->GetTexture()->GetWidth() / 2.0f,
		sprite->GetTexture()->GetHeight() / 2.0f);

	moveAngle = 0;
}

void MyAnimator::InitAnimation(std::string path)
{
	animator->PushBackFrame(path);
}

void MyAnimator::Move(std::string path1, std::string path2, std::string path3)
{
	animator->PushBackFrame(path1);
	animator->PushBackFrame(path2);
	animator->PushBackFrame(path1);
	animator->PushBackFrame(path3);
	animator->speed = 10;
	animator->GetGameObject()->rotationCenter.SetVector(
		animator->GetTexture(0)->GetWidth() / 2.0f,
		animator->GetTexture(0)->GetWidth() / 2.0f);

	moveAngle = 0;
}