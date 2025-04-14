#pragma once
#include "Core.h"
#include "Layer.h"

namespace Echo {

	/// @brief 层栈
	class ECHO_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

	public:
		/// @brief 添加一个层到栈：此函数用于在层栈中添加一个新的层, 并使层栈索引+1
		/// @param layer 
		void PushLayer(Layer* layer);
		/// @brief 添加一个层到栈：此函数用于在层栈顶部(即容器尾部)添加一个新的层
		/// @param overlay 
		void PushOverlay(Layer* overlay);
		/// @brief 从层堆栈中移除指定的层：此函数用于从层栈中移除一个指定层, 并使层栈索引-1
		/// @param layer 
		void PopLayer(Layer* layer);
		/// @brief 从层堆栈中移除指定的层：此函数用于从层栈中移除一个指定层, 并不改变层栈索引
		/// @param overlay 
		void PopOverlay(Layer* overlay);

	public:
		size_t Size() const { return m_Layers.size(); }
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

		Layer* operator[](size_t index);

	private:
		/// @brief 层栈索引
		uint32_t m_nLayerIndex = 0;
		/// @brief 层栈
		std::vector<Layer*> m_Layers;
	};

}
