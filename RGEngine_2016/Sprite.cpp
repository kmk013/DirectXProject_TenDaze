#include "Sprite.h"

Sprite::Sprite(std::string path)
{
	name = "sprite";

	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);
	auto col = AttachComponent<Components::BoxCollider>();
	col->box.SetRect(0.0f, 0.0f, (float)sprite->GetTexture()->GetWidth(), (float)sprite->GetTexture()->GetHeight());
}
Sprite::~Sprite()
{
}