#pragma once
#include "Core/Layer.h"

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
		virtual void OnRender() override;

		/// @brief 启动ImGUI框架
		void Begin();
		void End();
	};

}


