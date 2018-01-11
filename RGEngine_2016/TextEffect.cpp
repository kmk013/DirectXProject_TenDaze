#include "TextEffect.h"
#include "RGAssetManager.h"
#include "GameScene.h"

using namespace RGEngine;

TextEffect::TextEffect(string path)
{
	sprite = AttachComponent<Components::SpriteRenderer>();
	sprite->SetTexture(path);
	sprite->useOwnColor = true;
}

void TextEffect::OnUpdate() {
	position.y -= 300 * RGEngine::deltaTime();
	sprite->tenDazeColor.a = sprite->tenDazeColor.a - RGEngine::deltaTime() < 0 ? 0 : sprite->tenDazeColor.a - RGEngine::deltaTime();
	
	if (sprite->tenDazeColor.a <= 0)
		Destroy();
}