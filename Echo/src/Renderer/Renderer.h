#pragma once
#include "Core.h"

#include "Shader.h"
#include "Camera.h"
#include "RendererAPI.h"

namespace Echo {

	/// @brief 渲染器类
	class ECHO_API Renderer
	{
	public:
		/// @brief 获取当前渲染API
		/// @return 
		static RenderAPIType GetAPI() { return RendererAPI::GetAPIType(); }

	public:
		/// @brief 初始化渲染器
		static void InitRenderer();
		/// @brief 窗口尺寸修改
		/// @param width 
		/// @param height 
		static void WindowResize(uint32_t width, uint32_t height);
		/// @brief 开始屏幕渲染
		static void BeginScene(const Camera& camera);
		/// @brief 结束屏幕渲染
		static void EndScene();

		/// @brief 提交渲染用的顶点数组
		/// @param shader 着色器
		/// @param vertexArray 顶点数组
		/// @param transform 变换矩阵
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}
