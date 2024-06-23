#pragma once
#include <NestUI.h>

#include "Core/DockWidgetManager.h"

namespace Nest {

	class Windows_MainWindow : public NestUI::MainWindow
	{
		Q_OBJECT
	public:
		Windows_MainWindow(const NestUI::sWindowProps& prop);
		virtual ~Windows_MainWindow();

	public:
		virtual unsigned int GetWidth() const override { return m_sData.m_nWidth; }
		virtual unsigned int GetHeigth() const override { return m_sData.m_nHeight; }
		virtual QString GetTitle() const override { return m_sData.m_STitle; }

		/// @brief 设置垂直同步
		/// @param enabled 
		void SetVSync(bool enabled);
		/// @brief 是否开启了垂直同步
		/// @return 
		bool IsVSync() const { return m_sData.m_bVSync; }

		/// @brief 初始化DockWidgets
		void InitializeDockWidgets();
		/// @brief 初始化GLFW
		void InitializeGLWidget();

		/// @brief 获取dockWidget
		/// @param STitle dockWidget对应的窗口标题
		/// @return 
		NestUI::DockWidget* GetDockWidget(const QString& STitle);

	private:
		/// @brief 初始化
		virtual void Initialize(const NestUI::sWindowProps& props);
		/// @brief 窗口关闭
		virtual void ShutDown();

	private:
		/// @brief 窗口数据
		typedef struct sWindowData
		{
			unsigned int m_nWidth = 0;
			unsigned int m_nHeight = 0;
			QString m_STitle;
			bool m_bVSync = true;	//是否开启垂直同步
		}sWindowData;

		sWindowData m_sData;

		DockWidgetManager* m_dockManager;
	};

}


