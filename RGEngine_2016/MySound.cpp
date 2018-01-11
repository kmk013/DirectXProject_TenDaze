#include "MySound.h"



MySound::MySound()
{
	jump = new SoundTest("resources/Sound/Jump.wav");
	bow = new SoundTest("resources/Sound/Bow.wav");
	gun = new SoundTest("resources/Sound/Gun.wav");
	main = new SoundTest("resources/Sound/Main.mp3");

	
}


MySound::~MySound()
{
}
