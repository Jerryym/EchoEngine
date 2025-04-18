#pragma once
#include "Core.h"
#include "entt.hpp"

namespace Echo {

	class Scene;

	/// @brief 实体类: 类似于Unity中的GameObject
	class ECHO_API Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, const std::string& name, Scene* scene);
		virtual ~Entity() = default;

		operator bool() const;

	public:
		/// @brief 添加组件
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			ECHO_CORE_ASSERT(HasComponent<T>() == true, "Entity already has component!");
			return m_pScene->AddComponent<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		/// @brief 获取组件
		template<typename T>
		T& GetComponent()
		{
			ECHO_CORE_ASSERT(HasComponent<T>() != true, "Entity does not have component!");
			return m_pScene->GetComponent<T>(m_EntityHandle);
		}

		/// @brief 判断组件是否存在
		template<typename T>
		bool HasComponent() const
		{
			return m_pScene->HasComponent<T>(m_EntityHandle);
		}

		/// @brief 移除组件
		template<typename T>
		void RemoveComponent()
		{
			ECHO_CORE_ASSERT(HasComponent<T>() != true, "Entity does not have component!");
			m_Scene->RemoveComponent<T>(m_EntityHandle);
		}

	public:
		/// @brief 获取实体名称
		/// @return 
		const std::string& GetName() const { return m_sName; }

	private:
		/// @brief Entity句柄
		entt::entity m_EntityHandle = entt::null;
		/// @brief 实体名称
		std::string m_sName;
		/// @brief Entity所属的场景指针
		Scene* m_pScene = nullptr;
	};

}
