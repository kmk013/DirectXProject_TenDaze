#include "WhipEffect.h"

#include "RGEngine.h"

WhipEffect::WhipEffect(Math::Vector pos, string path, int amount) : isInit(false)
{
	for (int i = 0; i < amount; i++)
	{
		Sprite *p = new Sprite(path);
		p->position = pos;

		p->rotationCenter = Math::Vector(p->sprite->GetTexture()->GetWidth(), p->sprite->GetTexture()->GetHeight()) / 2;
		p->sprite->useOwnColor = true;
		float rotation = Math::Random(D3DXToRadian(-120), D3DXToRadian(-60));
		Math::Vector speed = Math::Vector(Math::Random(100, 400) * cos(rotation), Math::Random(100, 400) * sin(rotation));

		Particle particle = { p, speed, 0 };
		particleList.push_back(particle);
	}
}

void WhipEffect::OnUpdate()
{
	RGEngine::Scene *gameScene = RGApp->GetScene();

	if (!isInit)
	{
		isInit = true;

		for each (Particle p in particleList)
			gameScene->PushBackGameObject(p.spr);
	}

	for (auto iter = particleList.begin(); iter != particleList.end(); iter++)
	{
		Math::Vector beforePos = iter->spr->position;
		iter->spr->position += iter->speed * 0.02f + Math::Vector(0, iter->gravity += 9.8 * RGEngine::deltaTime() * 1.5f);
		iter->spr->rotate = atan2(beforePos.y - iter->spr->position.y, beforePos.x - iter->spr->position.x);
		iter->spr->sprite->tenDazeColor.a -= RGEngine::deltaTime() * 2;
		if (iter->spr->sprite->tenDazeColor.a <= 0)
		{
			iter->spr->Destroy();
			iter = particleList.erase(iter);
			if (iter == particleList.end())
				break;
		}
	}

	if (particleList.empty())
		Destroy();
}