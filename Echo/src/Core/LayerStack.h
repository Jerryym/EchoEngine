#pragma once
#include "Layer.h"

namespace Echo {

	/// @brief 层栈：
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		/// @brief 从栈的第一个元素添加一个层级
		/// @param layer 
		void PushLayer(Layer* layer);
		/// @brief 添加一个层到栈
		/// @param overlay 离屏幕最远的layer
		void PushOverlay(Layer* overlay);
		/// @brief 将最外的层取出来
		/// @param layer 
		void PopLayer(Layer* layer);
		/// @brief 从列表中取出一个层
		/// @param overlay 离屏幕最远的layer
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		unsigned int m_nInsertIndex;
		std::vector<Layer*> m_Layers;		//层栈
	};

}


