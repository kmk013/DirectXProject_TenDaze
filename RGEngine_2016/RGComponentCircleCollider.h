#ifndef _RGCOMPONENTCIRCLECOLLIDER_H_
#define _RGCOMPONENTCIRCLECOLLIDER_H_

#include "RGComponentCollider.h"
#include "RGMath.h"

namespace RGEngine
{
	namespace Components
	{
		class CircleCollider : public Collider
		{
		public:
			Math::Circle circle; // ¿ùµå ÁÂÇ¥¿¡¼­ transformÀÇ ÁÂÇ¥(¿ÞÂÊ À§) ±âÁØ
			Math::Circle GetCircleWithPosition(void) const;

		public:
			CircleCollider(GameObject *gameObject);
			~CircleCollider() override;

		public:
			void Reset(void) override;
			std::type_index GetID(void) override { return typeid(CircleCollider); }
			static std::type_index GetFamilyID(void) { return typeid(Collider); }

		public:
			// OnCreate -> Constructor
			// OnDestroy -> Destroyer
			void OnUpdate(void) override;

		};
	}
}

#endif // _RGCOMPONENTCIRCLECOLLIDER_H_