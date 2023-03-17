#pragma once
#include "Echo/Window.h"

#include <GLFW/glfw3.h>

namespace Echo {

	class Windows_Window :	public Window
	{
	public:
		Windows_Window(const sWindowProps& prop);
		virtual ~Windows_Window();

		virtual void OnUpdate() override;

		unsigned int GetWidth() const override { return m_sData.m_nWidth; }
		unsigned int GetHeight() const override { return m_sData.m_nHeight; }

		virtual void SetEventCallBack(const EventCallBackFun& callback) override;
		virtual void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return m_pWindow; }

	private:
		/// @brief ��ʼ��
		virtual void Initialize(const sWindowProps& props);

		/// @brief ���ڹر�
		virtual void ShutDown();

	private:
		GLFWwindow* m_pWindow;
		
		/// @brief ��������
		typedef struct sWindowData
		{
			unsigned int m_nWidth;
			unsigned int m_nHeight;
			std::string m_strTitle;
			bool m_bVSync;	//�Ƿ�����ֱͬ��
			EventCallBackFun m_Eventcallback;	//�¼��ص�����
		}sWindowData;

		sWindowData m_sData;

	};

}


