#include "echopch.h"
#include "Entity.h"

namespace Echo {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_pScene(scene)
	{
	}

	Entity::operator bool() const
	{
		return (m_EntityHandle != entt::null);
	}

}
