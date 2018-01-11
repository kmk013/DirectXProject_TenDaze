#ifndef _RGGAMEOBJECT_H_
#define _RGGAMEOBJECT_H_

#include <map>
#include <vector>
#include <cassert>
#include <typeindex>
#include "RGMath.h"

namespace RGEngine
{
	// reference
	class Scene;
	class Component;

	class GameObject
	{
	private:
		std::map<std::type_index, Component *> m_components;
		bool m_enabled;
		bool m_destroyed;

	public:
		std::string tag;
		std::string name;
		GameObject *parent;

		Math::Matrix matrix;
		Math::Vector position;
		Math::Vector center;
		Math::Vector scale;
		Math::Vector rotationCenter;
		Math::Vector scalingCenter;
		float rotate;
		float scalingRotation;

	public:
		GameObject(void);
		virtual ~GameObject();

	public:
		void SetEnabled(bool flag);
		bool GetEnabled(void) const;

		template<typename T>
		T* AttachComponent(void);
		template<typename T>
		void DetachComponent(void);
		template<typename T>
		T* GetComponent(void);

		void Update(void);
		void Render(void);
		void Destroy(void);

		bool GetDestroyed(void) const { return m_destroyed; }

	public:
		// OnCreate -> Constructor
		// OnDestroy -> Destroyer
		virtual void OnEnabled(void) {}
		virtual void OnDisabled(void) {}
		virtual void OnUpdate(void) {}
		virtual void OnAfterUpdate(void) {}
		virtual void OnRender(void) {}
		virtual void OnAfterRender(void) {}
		virtual void OnCollision(GameObject *col) {}

	};

	template<typename T>
	T* GameObject::AttachComponent(void)
	{
		std::type_index i(T::GetFamilyID());
		if (m_components.count(i) > 0)
		{
			delete m_components[i];
		}
		T *component = new T(this);
		m_components[i] = component;
		return component;
	}
	template<typename T>
	void GameObject::DetachComponent(void)
	{
		std::type_index i(T::GetFamilyID());
		T *component = m_components[i];
		if (component != NULL)
		{
			delete component;
		}
		m_components.erase(i);
	}
	template<typename T>
	T* GameObject::GetComponent(void)
	{
		std::type_index i(T::GetFamilyID());
		if (m_components.count(i) <= 0)
		{
			return NULL;
		}
		return static_cast<T*>(m_components[i]);
	}
}
#endif // _RGGAMEOBJECT_H_