#pragma once
#include "Core.h"
#include "entt.hpp"

#include "Entity.h"

namespace Echo {

	/// @brief 场景类
	class ECHO_API Scene
	{
	public:
		Scene();
		~Scene();

	public:
		/// @brief 创建实体
		/// @param name 实体名称
		/// @return 
		Entity CreateEntity(const std::string& name = std::string());

	private:
		/// @brief 向指定实体添加组件
		/// @tparam T 要添加的组件类型
		/// @tparam ...Args 构造组件 T 所需的参数类型列表
		/// @param handle 实体的句柄
		/// @param ...args 构造组件 T 的参数
		/// @return 返回添加到实体上的组件 T 的引用
		template<typename T, typename... Args>
		T& AddComponent(const entt::entity& handle, Args&&... args)
		{
			return m_Registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		/// @brief 获取指定实体中的组件
		/// @tparam T 要获取的组件类型
		/// @param handle 实体的句柄
		/// @return 返回获取的组件 T 的引用
		template<typename T>
		T& GetComponent(const entt::entity& handle) 
		{
			return m_Registry.get<T>(handle);
		}

		/// @brief 判断指定实体中是否存在T类型的组件
		/// @tparam T 组件类型
		/// @param handle 实体的句柄
		/// @return true-存在， false-不存在
		template<typename T>
		bool HasComponent(const entt::entity& handle) 
		{
			return m_Registry.any_of<T>(handle);
		}

		/// @brief 删除指定实体中的组件
		/// @tparam T 组件类型
		/// @param handle 实体的句柄
		template<typename T>
		void RemoveComponent(const entt::entity& handle)
		{
			m_Registry.remove<T>(handle);
		}

	private:
		/// @brief entt注册器
		entt::registry m_Registry;

		friend class Entity;
	};

}
