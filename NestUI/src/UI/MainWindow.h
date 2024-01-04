#pragma once
#include <QMainWindow>
#include "NestUICore.h"

namespace NestUI {

	/// @brief 窗口属性
	typedef struct NESTUI_API sWindowProps
	{
		unsigned int m_nWidth;		//窗口宽
		unsigned int m_nHeight;		//窗口高
		QString m_STitle;			//窗口标题

		sWindowProps(unsigned int width = 1600, unsigned int height = 900,
			const QString& title = "Nest FrameWork")
			: m_nWidth(width), m_nHeight(height), m_STitle(title)
		{

		}
	}sWindowProps;

	/// @brief 主窗口
	class NESTUI_API MainWindow : public QMainWindow
	{
		Q_OBJECT
	public:
		virtual ~MainWindow() {}

	public:
		/// @brief 获取主窗口宽度
		/// @return 
		virtual unsigned int GetWidth() const = 0;
		/// @brief 获取主窗口高度
		/// @return 
		virtual unsigned int GetHeigth() const = 0;
		/// @brief 获取主窗口标题名
		/// @return 
		virtual QString GetTitle() const = 0;
	};

}


