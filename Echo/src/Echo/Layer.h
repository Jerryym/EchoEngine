#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Echo {

	class ECHO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		/// @brief ���㱻����ʱ����layer��ӵ�layer stack��ʱ�����ô˺���
		virtual void OnAttach();
		/// @brief ���㱻����ʱ����layer��layer stack�Ƴ���ʱ�����ô˺������൱��Shutdown����
		virtual void OnDetach();
		/// @brief ���²�
		virtual void OnUpdate();
		/// @brief ImGui��Ⱦ
		virtual void OnImGuiRender();
		/// @brief ��������������е��¼�
		/// @param event ���е��¼�
		virtual void OnEvent(Event& event);

		const std::string& getName() const { return m_sLayerName; }

	protected:
		std::string m_sLayerName;		//����
	};

}