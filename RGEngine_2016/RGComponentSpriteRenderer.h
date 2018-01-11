#ifndef _RGCOMPONENTSPRITERENDERER_H_
#define _RGCOMPONENTSPRITERENDERER_H_

#include "RGComponentRenderer.h"
#include "RGAssetManager.h"
#include "RGMath.h"

namespace RGEngine
{
	namespace Components
	{
		class SpriteRenderer : public Renderer
		{
		private:
			Assets::Texture *m_texture;

		public:
			SpriteRenderer(GameObject *gameObject);
			~SpriteRenderer() override;
			
			Assets::Texture* GetTexture(void) const;
			void SetTexture(std::string path);
			
			bool useOwnColor;
			Math::Color tenDazeColor;
			
		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(SpriteRenderer); }
			static std::type_index GetFamilyID(void) { return typeid(Renderer); }

		public:
			// OnCreate -> Constructor
			// OnDestroy -> Destroyer
			void OnRender(void) override;

		};
	}
}

#endif // _RGCOMPONENTSPRITERENDERER_H_