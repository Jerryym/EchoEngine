#pragma once
#include "Core/Events/Event.h"

namespace Echo {

	/// @brief 图层类：用于管理引擎中的事件和更新逻辑/渲染逻辑
	class Layer
	{
	public:
		Layer(const std::string& sLayerName);
		virtual ~Layer() {}

	public:
		/// @brief 图层附加应用程序：此函数在层附加到应用程序的层栈(LayerStack)时调用
		virtual void OnAttach() {}
		/// @brief 图层分离应用程序：此函数在层从应用程序的层栈(LayerStack)中移除时调用
		virtual void OnDetach() {}
		/// @brief 更新图层：此函数在主循环中每帧调用，用于处理逻辑更新
		virtual void OnUpdate() {}
		/// @brief 处理事件：此函数在主循环中每帧调用，用于处理图层中事件
		/// @param event 需处理事件
		virtual void OnEvent(Event& event) {}

		/// @brief 获取层名
		/// @return 
		inline const std::string& GetName() const { return m_sLayerName; }

	protected:
		/// @brief 层名
		std::string m_sLayerName;
	};

}

