#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class Text : public RGEngine::GameObject
{
public:
	Components::TextRenderer *text;

public:
	Text(std::string font, unsigned int size, unsigned int weight = FW_NORMAL);
	~Text() override;

};

