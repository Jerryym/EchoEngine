#pragma once
#include "Core/Layer.h"

#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/MouseEvent.hpp"
#include "Core/Events/KeyEvent.hpp"

namespace Echo {

	/// @brief 
	class ImGUILayer : public Layer
	{
	public:
		ImGUILayer();
		virtual ~ImGUILayer();

	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnRenderUI() override;

		/// @brief 启动ImGUI框架
		void Begin();
		void End();
	};

}


