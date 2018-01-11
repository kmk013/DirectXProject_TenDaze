#include "MouseCamera.h"


MouseCamera::MouseCamera()
{
	button = new InGameButton();
	scene = new Scene();
}


MouseCamera::~MouseCamera()
{
}

void MouseCamera::OnUpdate()
{
	RGInput->GetMouseFromClient(mouse);
	cout << scene->GetCamera()->position.x << endl;

	if (mouse.x < 175)
	{
		if (scene->GetCamera()->position.x >= 0) {}
		else
		{
			scene->GetCamera()->position.x += 5;
			button->ui[0]->position.x -= 5;
			button->ui[1]->position.x -= 5;
			button->ui[2]->position.x -= 5;
			button->ui[3]->position.x -= 5;
			button->ui[4]->position.x -= 5;
			button->ui[5]->position.x -= 5;
		}
	}
	else if (mouse.x > 825)
	{
		if (scene->GetCamera()->position.x <= -1024) {}
		else
		{
			scene->GetCamera()->position.x -= 5;
			button->ui[0]->position.x += 5;
			button->ui[1]->position.x += 5;
			button->ui[2]->position.x += 5;
			button->ui[3]->position.x += 5;
			button->ui[4]->position.x += 5;
			button->ui[5]->position.x += 5;
		}
	}
}