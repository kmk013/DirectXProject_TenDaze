#pragma once
#include "RGEngine.h"

#include "InGameButton.h"

#include "Japan.h"

using namespace RGEngine;

class MouseCamera : public RGEngine::GameObject
{
public:
	MouseCamera();
	~MouseCamera();

	InGameButton *button;
	Scene *scene;

	Math::Vector mouse;

	void OnUpdate();
};

