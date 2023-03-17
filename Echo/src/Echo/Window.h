#pragma once

#include "echopch.h"
#include "Core.h"
#include "Events/Event.h"


namespace Echo {

	/// @brief ��������
	typedef struct sWindowProps
	{
		unsigned int m_nWidth;		//���ڿ�
		unsigned int m_nHeight;		//���ڸ�
		std::string m_strTitle;		//���ڱ���

		sWindowProps(unsigned int width = 1600, unsigned int height = 900,
			const std::string& title = "Echo Engine")
			: m_nWidth(width), m_nHeight(height), m_strTitle(title)
		{

		}
	}sWindowProps;


	/// @brief ��������ϵͳ�� Window �ӿ�
	class ECHO_API Window
	{
	public:
		/// @brief �¼��ص�����
		using EventCallBackFun = std::function<void(Event&)>;
		
		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		////////////////////////////////////////////////////////////////////
		// ��������
		/// @brief �����¼��ص�����
		/// @param callback 
		virtual void SetEventCallBack(const EventCallBackFun& callback) = 0;
		
		/// @brief ���ô�ֱͬ��
		/// @param enabled 
		virtual void SetVSync(bool enabled) = 0;

		/// @brief �Ƿ����˴�ֱͬ��
		/// @return ��ֱͬ������״̬
		virtual bool IsVSync() const = 0;
		////////////////////////////////////////////////////////////////////

		/// @brief ��ȡ��ǰ�����
		/// @return ��ǰ�����ָ��
		virtual void* GetNativeWindow() const = 0;

		/// @brief ��������
		/// @param props ��������
		/// @return ����ָ��
		static Window* Create(const sWindowProps& props = sWindowProps());

	};

}