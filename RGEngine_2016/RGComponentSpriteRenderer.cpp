#include "RGComponentSpriteRenderer.h"

#include "RGApplication.h"

namespace RGEngine
{
	namespace Components
	{
		SpriteRenderer::SpriteRenderer(GameObject *gameObject) : Renderer(gameObject), tenDazeColor(1.0f,1.0f,1.0f,1.0f), useOwnColor(false)
		{
			Reset();
		}
		SpriteRenderer::~SpriteRenderer() {}
		Assets::Texture* SpriteRenderer::GetTexture(void) const
		{
			return m_texture;
		}
		void SpriteRenderer::SetTexture(std::string path)
		{
			if (RGAssetTexture->Get(path) == NULL)
			{
				RGAssetTexture->Load(path);
			}
			m_texture = RGAssetTexture->Get(path);
		}
		void SpriteRenderer::Reset(void)
		{
			m_texture = NULL;
		}
		void SpriteRenderer::OnRender(void)
		{
			if (m_texture)
			{
				if (useOwnColor)
					m_texture->TenDazeBlt(&tenDazeColor);
				else
					m_texture->Blt();
			}
		}
	}
}