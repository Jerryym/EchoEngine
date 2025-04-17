#include "echopch.h"
#include "Scene.h"

#include "Component.h"

namespace Echo {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		std::string sName = name.empty() ? "Entity" : name;
		Entity entity{ m_Registry.create(), name, this };
		entity.AddComponent<TransformComponent>();
		return entity;
	}

}
