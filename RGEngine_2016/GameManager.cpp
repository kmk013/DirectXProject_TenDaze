#include "GameManager.h"
#include <fstream>

GameManager *GameManager::instance = nullptr;

GameManager *GameManager::GetInstance() {
	if (instance == nullptr)
		instance = new GameManager();
	return instance;
}

GameManager::GameManager() : whipPower(1), hasTearCount(0), howDeveloped(0), isFirstBlueScreen(true), isFirstTropicana(true), isFirstAddict(true), sleepTime(0), allTearCount(0), howDrinkCan(0), howHitDeveloper(0)
{
	ifstream openFile("resources/data.txt");
	for (int i = 0; i < 6; i++)
	{
		endingOpened[i] = openFile.get() - 48;
		whipPower += endingOpened[i];
	}
	openFile.close();

	if (endingOpened[TROPICANA_ENDING] == 1)
		isFirstTropicana = false;
	if (endingOpened[BLUE_SCREEN_ENDING] == 1)
		isFirstBlueScreen = false;
	if (endingOpened[ADDICT_ENDING] == 1)
		isFirstAddict = false;
}

GameManager::~GameManager()
{
}

void GameManager::Reset()
{
	hasTearCount = (0), howDeveloped = (0), sleepTime = (0), allTearCount = (0), howDrinkCan = (0), howHitDeveloper = 0;
}