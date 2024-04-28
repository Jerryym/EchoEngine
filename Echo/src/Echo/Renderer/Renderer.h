#pragma once
#include "RenderCommond.h"
#include "Camera.h"
#include "Shader.h"

namespace Echo {

	class Renderer
	{
	public:
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		/// @brief 开始屏幕渲染
		static void BeginScene(const Camera& camera);
		
		/// @brief 结束屏幕渲染
		static void EndScene();

		/// @brief 提交渲染用的顶点数组
		/// @param shader 着色器
		/// @param name 着色器中uniform类型变量名
		/// @param vertexArray 顶点数组
		static void Submit(const std::shared_ptr<Shader>& shader, const std::string& name, const std::shared_ptr<VertexArray>& vertexArray);

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}
