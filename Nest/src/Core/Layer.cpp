#include "nestpch.h"
#include "Layer.h"

namespace Nest {

	Layer::Layer(const QString& name)
		: m_SLayerName(name)
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

	void Layer::SetValid(bool bValid)
	{
		m_bValid = bValid;
	}

	void Layer::OnKeyPressedEvent(int key)
	{
	}

	void Layer::OnMouseButtonPressedEvent(int button)
	{
	}

	void Layer::OnMouseMoveEvent(double xpos, double ypos)
	{
	}

}
