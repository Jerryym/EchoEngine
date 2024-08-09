#pragma once
#include "Camera/EditorCamera.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace Echo {

	/// @brief 2D渲染器
	class Renderer2D
	{
	public:
		/// @brief 渲染器初始化
		static void Initialize();
		/// @brief 渲染器关闭
		static void ShutDown();

		/// @brief 开始屏幕渲染
		static void BeginScene(const EditorCamera& camera);
		/// @brief 结束屏幕渲染
		static void EndScene();

	public:
		/// @brief 绘制四边形
		/// @param position 四边形的中心位置，使用二维向量表示（x, y）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param color 四边形的颜色，使用四维向量表示（红, 绿, 蓝, 透明度）
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		/// @brief 绘制四边形
		/// @param position 四边形的中心位置，使用三维向量表示（x, y, z）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param color 四边形的颜色，使用四维向量表示（红, 绿, 蓝, 透明度）
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		/// @brief 绘制四边形
		/// @param position 四边形的中心位置，使用二维向量表示（x, y）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param texture 2D纹理
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		/// @brief 绘制四边形
		/// @param position 四边形的中心位置，使用三维向量表示（x, y, z）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param texture 2D纹理
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};

	/// @brief 2D渲染数据
	typedef struct Renderer2DData
	{
		/// @brief 顶点数组
		Ref<VertexArray> m_VertexArray;
		/// @brief 2D纹理
		Ref<Texture2D> m_Texture;
		/// @brief 着色器
		Ref<Shader> m_Shader;

	}Renderer2DData;

}
