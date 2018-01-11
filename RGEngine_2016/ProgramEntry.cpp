#include "RGEngine.h"
#include "GameScene.h"
#include "MainScene.h"

int main(void)
{
	RGApp->Initialize(L"Ten Daze", 1920, 1080, true);
	RGAsset->Initialize();

	RGApp->ChangeScene(new MainScene());

	while (RGGraphic->Validate())
	{
		if (RGGraphic->Process())
		{
			RGApp->Update();

			if (RGGraphic->BeginScene())
			{
				RGApp->Render();

				RGGraphic->EndScene();
			}
		}
	}

	return 0;
}