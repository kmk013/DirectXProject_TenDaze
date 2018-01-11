#pragma once
#include "RGEngine.h"

using namespace RGEngine;

class GameManager
{
private:
	static GameManager* instance;
public:
	GameManager();
	~GameManager();

	static GameManager* GetInstance();

	int whipPower;          
	int hasTearCount;  
	float howDeveloped;
	int sleepTime;
	int allTearCount;
	int howDrinkCan;
	int howHitDeveloper;

	int endingOpened[6];

	bool isFirstTropicana;
	bool isFirstBlueScreen;
	bool isFirstAddict;

	void Reset();
};

