#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Echo {

	/// @brief ��ջ�����ڴ�Ź��������еĲ�
	class ECHO_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		/// @brief ��ջ�ĵ�һ��Ԫ�����һ���㼶
		/// @param layer 
		void PushLayer(Layer* layer);
		/// @brief ���һ���㵽ջ
		/// @param overlay ����Ļ��Զ��layer
		void PushOverlay(Layer* overlay);
		/// @brief ������Ĳ�ȡ����
		/// @param layer 
		void PopLayer(Layer* layer);
		/// @brief ���б���ȡ��һ����
		/// @param overlay ����Ļ��Զ��layer
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		unsigned int m_nInsertIndex;
		std::vector<Layer*> m_Layers;		//��ջ
	};

}


