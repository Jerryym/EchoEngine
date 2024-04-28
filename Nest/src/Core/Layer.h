#pragma once
#include "NestCore.h"

namespace Nest {

	/// @brief 渲染引擎中的层（Layer）的基类。
	class NEST_API Layer
	{
	public:
		Layer(const QString& name = "Layer");
		virtual ~Layer() {}

	public:
		/// @brief 当层被添加到层栈时调用，用于执行一次性初始化操作。
		virtual void OnAttach();
		/// @brief 当层从层栈移除时调用，用于执行清理和资源释放操作。
		virtual void OnDetach();
		/// @brief 更新层
		virtual void OnUpdate();
		/// @brief 获取层名
		/// @return 返回层名
		QString getName() const { return m_SLayerName; }
		/// @brief 设置层是否有效
		/// @param bValid 
		void SetValid(bool bValid);
		bool IsValid() const { return m_bValid; }

	public:
		/// @brief 处理按键按下事件
		/// @param key 
		virtual void OnKeyPressedEvent(int key);
		/// @brief 处理鼠标按下事件
		/// @param button 
		virtual void OnMouseButtonPressedEvent(int button);
		/// @brief 处理鼠标移动事件
		/// @param xpos 
		/// @param ypos 
		virtual void OnMouseMoveEvent(double xpos, double ypos);

	protected:
		/// @brief 层名
		QString m_SLayerName;
		/// @brief 当前层是否有效
		bool m_bValid = false;
	};

}


