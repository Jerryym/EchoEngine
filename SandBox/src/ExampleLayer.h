#pragma once
#include <Echo.h>

namespace SandBoxApp {

	class ExampeleLayer : public Echo::Layer
	{
	public:
		ExampeleLayer();
		virtual ~ExampeleLayer();

	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate(Echo::TimeStep ts) override;
		virtual void OnRenderUI() override;
		virtual void OnEvent(Echo::Event& e) override;

	private:
		/// @brief 绘制立方体
		void DrawCube();

	private:
		/// @brief 相机
		Echo::Camera m_Camera;
		/// @brief 顶点数组对象
		Echo::Ref<Echo::VertexArray> m_CubeVA;
		/// @brief 着色器库
		Echo::ShaderLibrary m_ShaderLib;
		/// @brief 纹理
		Echo::Ref<Echo::Texture2D> m_Texture;

		/// @brief 立方体颜色
		glm::vec3 m_CubeColor = glm::vec3(0.5, 0.5, 0.5);
	};

}
