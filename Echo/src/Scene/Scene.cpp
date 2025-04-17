#include "echopch.h"
#include "Scene.h"

namespace Echo {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity{ m_Registry.create(),this };
		return entity;
	}

}
