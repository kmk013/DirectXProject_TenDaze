#pragma once
#include "RGEngine.h"

#include "Timer.h"
#include "UI.h"
#include "Animation.h"
#include "Sound.h"

class Developer : public RGEngine::GameObject
{
public:
	Developer();

	bool isDead;
	float exhaustion;
	float hp;
	float maxHp;
	float lastHp;

	bool isInit;

	Animation *developerAni;
	Animation *monitorAni;
	
	Animation *spakDeveloperAni;
	Animation *spakMonitorAni;

	Sound *whipSound;
	Sound *deathSound;
	Sound *blueScreenSound;

	void ChangeAnimation(PlayerState state);
	void MonitorReset();
	void OnUpdate();
	void Hit();
	void PlusHp(int amount);
};

