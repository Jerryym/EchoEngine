#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Echo {

	class ECHO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		/// @brief 当层被吸附时，当layer添加到layer stack的时候会调用此函数
		virtual void OnAttach();
		/// @brief 当层被分离时，当layer从layer stack移除的时候会调用此函数，相当于Shutdown函数
		virtual void OnDetach();
		/// @brief 更新层
		virtual void OnUpdate();
		/// @brief ImGui渲染
		virtual void OnImGuiRender();
		/// @brief 处理层上正在运行的事件
		/// @param event 运行的事件
		virtual void OnEvent(Event& event);

		const std::string& getName() const { return m_sLayerName; }

	protected:
		std::string m_sLayerName;		//层名
	};

}