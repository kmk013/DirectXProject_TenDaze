#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class MyAnimator : public RGEngine::GameObject
{
public:
	MyAnimator();
	MyAnimator(std::string path);
	~MyAnimator();

	Components::SpriteRenderer *sprite;
	Components::AnimationRenderer *animator;
	float moveAngle;

	void InitImage(std::string path);
	void InitAnimation(std::string path);
	void Move(std::string path1, std::string path2, std::string path3);
};

