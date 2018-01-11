#pragma once
#include "RGGameObject.h"
#include "Sprite.h"
#include "Developer.h"
#include "UI.h"
#include "Sound.h"

class Developer;

class Timer : public RGEngine::GameObject
{
public:
	Timer();
	~Timer();

private:

	float checker = 0.0f;

public:

	int hour = 0;
	int minute = 0;
	int day = 1;

	int blueScreenTimer;

	bool isSleep;
	bool isAm;	//true==am, false==pm

	bool isInit;

	bool isDayVisible;
	bool isDayFadein;

	Sound *wakeUpSound;

	Sprite *calendar[11];
	Sprite *hourText[2][10];
	Sprite *minuteText[2][10];
	void InitTimer();
	void OnUpdate() override;
	void OnEnd();

	void TimeCountOnAwake();
	void TimeCountOnSleep();
	void ShowBlackScreen(bool fadein);
	void ShowDayText();

	void CalendarUpdate();
	void WatchUpdate();
};

