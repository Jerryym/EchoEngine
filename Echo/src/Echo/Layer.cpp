#include "echopch.h"
#include "Layer.h"

namespace Echo {

	Layer::Layer(const std::string& name)
		: m_sLayerName(name)
	{
	}

	Layer::~Layer()
	{
	}
	
	void Layer::OnAttach()
	{
	}
	
	void Layer::OnDetach()
	{
	}
	
	void Layer::OnUpdate()
	{
	}

	void Layer::OnEvent(Event& event)
	{
	}

}