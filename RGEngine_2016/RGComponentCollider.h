#ifndef _RGCOMPONENTCOLLIDERRENDERER_H_
#define _RGCOMPONENTCOLLIDERRENDERER_H_

#include "RGComponent.h"

namespace RGEngine
{
	namespace Components
	{
		class Collider : public Component
		{
		public:
			Collider(GameObject *gameObject);
			virtual ~Collider() override {}

		public:
			virtual void Reset(void) override {}
			virtual std::type_index GetID(void) override = 0 { return typeid(Collider); }
			static std::type_index GetFamilyID(void) { return typeid(Collider); }

		public:
			// OnCreate -> Constructor
			// OnDestroy -> Destroyer
			virtual void OnUpdate(void) override {}

		};
	}
}

#endif // _RGCOMPONENTCOLLIDERRENDERER_H_