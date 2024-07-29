#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Echo {

	/// @brief 渲染器类
	class Renderer
	{
	public:
		/// @brief 获取当前渲染API
		/// @return 
		static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
		/// @brief 开始屏幕渲染
		static void BeginScene(Camera& camera);
		/// @brief 结束屏幕渲染
		static void EndScene();

		/// @brief 提交渲染用的顶点数组
		/// @param shader 着色器
		/// @param vertexArray 顶点数组
		/// @param transform 变换矩阵
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}


