#ifndef _RGCOMPONENTRENDERER_H_
#define _RGCOMPONENTRENDERER_H_

#include "RGComponent.h"

namespace RGEngine
{
	namespace Components
	{
		class Renderer : public Component
		{
		public:
			Renderer(GameObject *gameObject) : Component(gameObject) {}
			~Renderer() override {}

		public:
			virtual void Reset(void) override {}
			virtual std::type_index GetID(void) override = 0 { return typeid(Renderer); }
			static std::type_index GetFamilyID(void) { return typeid(Renderer); }

		public:
			// OnCreate -> Constructor
			// OnDestroy -> Destroyer
			virtual void OnUpdate(void) override {}
			virtual void OnRender(void) override {}

		};
	}
}

#endif // _RGCOMPONENTRENDERER_H_