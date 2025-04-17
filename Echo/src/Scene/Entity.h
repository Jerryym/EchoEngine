#pragma once
#include "Core.h"
#include "entt.hpp"

namespace Echo {

	class Scene;

	class ECHO_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		virtual ~Entity() = default;

		operator bool() const;

	public:
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ECHO_CORE_ASSERT(HasComponent<T>() == true, "Entity already has component!");
			return m_pScene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args));
		}

		template<typename T>
		T& GetComponent()
		{
			ECHO_CORE_ASSERT(HasComponent<T>() != true, "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_pScene->m_Registry.any_of<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			ECHO_CORE_ASSERT(HasComponent<T>() != true, "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

	private:
		/// @brief Entity句柄
		entt::entity m_EntityHandle = entt::null;
		/// @brief Entity所属的场景指针
		Scene* m_pScene = nullptr;

		friend class Scene;
	};

}
