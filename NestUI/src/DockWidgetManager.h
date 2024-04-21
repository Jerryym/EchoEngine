#pragma once
#include "NestUICore.h"
#include "UI/MainWindow.h"

namespace NestUI {

	/// @brief DockWidget窗口管理类
	class NESTUI_API DockWidgetManager
	{
	public:
		/// @brief 获取当前DockManager
		/// @return 
		static DockWidgetManager* GetDockManager(QMainWindow* mainWindow);

		/// @brief 添加DockWidget
		/// @param STitle DockWidget对应的窗口标题
		/// @param dockWidget 
		/// @return 若对应窗口标题的dockwidget存在，返回false
		bool AddDockWidget(const QString& STitle, QDockWidget* dockWidget, Qt::DockWidgetArea area);

		/// @brief 获取DockWidget
		/// @param STitle DockWidget对应的窗口标题
		/// @return 
		QDockWidget* GetDockWidget(const QString& STitle);

		/// @brief 移除DockWidget
		/// @param STitle DockWidget对应的窗口标题
		void RemoveDockWidget(const QString& STitle);

		/// @brief 获取当前主窗口中的dockWidget个数
		/// @return 
		int GetDockWidgetNum() const { return m_DockWidgetMap.size(); }

	protected:
		DockWidgetManager(QMainWindow* mainWindow);
		~DockWidgetManager();

	private:
		/// @brief DockWidget窗口管理单例: 程序运行时，每个主窗口当且只能有一个DockManager存在
		static DockWidgetManager* s_Instance;
		QMainWindow* m_mainWindow;	//应用程序主窗口
		//dockWidget Map
		QMap<QString, QDockWidget*> m_DockWidgetMap;
	};

}


