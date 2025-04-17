#pragma once
#include "Core.h"
#include "entt.hpp"

#include "Entity.h"

namespace Echo {

	class ECHO_API Scene
	{
	public:
		Scene();
		~Scene();

	public:
		/// @brief 创建Entity
		/// @param name Entity Name
		/// @return 
		Entity CreateEntity(const std::string& name = std::string());

	private:
		/// @brief entt注册器
		entt::registry m_Registry;
	};

}
