#pragma once
#include <Echo.h>

namespace SandBoxApp {

	class ExampeleLayer : public Echo::Layer
	{
	public:
		ExampeleLayer();
		virtual ~ExampeleLayer();

	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnRenderUI() override;
		virtual void OnEvent(Event& e) override;
	};

}
