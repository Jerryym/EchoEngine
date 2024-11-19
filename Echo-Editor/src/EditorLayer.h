#pragma once
#include <Echo.h>

namespace Echo {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() {}

	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(TimeStep ts) override;
		virtual void OnRenderUI() override;
		virtual void OnEvent(Event& e) override;

	private:
		void CreateDockSpace(bool bEnable);

	private:
		/// @brief 纹理贴图
		Ref<Texture2D> m_Texture, m_Texture2;
		/// @brief 编辑器相机
		EditorCamera m_Camera;
		/// @brief 帧缓冲对象
		Ref<FrameBuffer> m_FBO;

		/// @brief 视口大小
		glm::vec2 m_ViewportSize = { 0,0 };
	};

}
