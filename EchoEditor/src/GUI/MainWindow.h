#pragma once

namespace EchoEditor {

	/// @brief 主窗口
	class MainWindow : public NestUI::NestMainWindow
	{
	public:
		MainWindow(const NestUI::sWindowProp& sProp = NestUI::sWindowProp(), QWidget* parent = nullptr);
		virtual ~MainWindow() {}

	public:
		/// @brief 获取窗口宽度
		virtual uint32_t GetWidth() const { return m_sData.m_nWidth; }
		/// @brief 获取窗口高度
		virtual uint32_t GetHeight() const { return m_sData.m_nHeight; }
		/// @brief 获取窗口标题
		virtual const QString& GetTitle() const override { return m_sData.m_STitle; }
		/// @brief 设置垂直同步
		/// @param enabled 
		void SetVSync(bool enabled);
		/// @brief 是否开启了垂直同步
		/// @return 
		bool IsVSync() const { return m_sData.m_bVSync; }

	private:
		/// @brief 初始化窗口
		/// @param sProp 窗口属性
		void Initialize(const NestUI::sWindowProp& sProp);
		/// @brief 初始化DockWidgets
		void InitializeDockWidgets();
		/// @brief 初始化GLWidget
		/// @param bVSync 是否开启垂直同步
		void InitializeGLWidget(bool bVsync);

	private:
		/// @brief 窗口数据
		typedef struct sWindowData
		{
			uint32_t m_nWidth = 0;
			uint32_t m_nHeight = 0;
			QString m_STitle;
			bool m_bVSync = true;	//是否开启垂直同步
		}sWindowData;

		/// @brief 窗口数据
		sWindowData m_sData;
		/// @brief 停靠窗口管理器
		NestUI::DockWidgetManager* m_pDockManager;
	};

}
