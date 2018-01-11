#include "Animation.h"

Animation::Animation()
{
	ani = AttachComponent<Components::AnimationRenderer>();
}

Animation::~Animation()
{
}

void Animation::SetCollider()
{
	auto col = AttachComponent<Components::BoxCollider>();
	col->box.SetRect(0.0f, 0.0f, (float)ani->GetTexture(0)->GetWidth(), (float)ani->GetTexture(0)->GetHeight());
}