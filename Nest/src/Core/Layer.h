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

	protected:
		QString m_SLayerName;		//层名
	};

}


