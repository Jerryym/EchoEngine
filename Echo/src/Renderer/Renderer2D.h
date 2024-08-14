#pragma once
#include "Camera/EditorCamera.h"

#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

namespace Echo {

	/// @brief 渲染统计数据
	typedef struct RenderStatistics
	{
		/// @brief 调用渲染命令次数
		uint32_t m_iDrawCalls = 0;
		/// @brief 四边形数量
		uint32_t m_iQuadCount = 0;

		uint32_t GetTotalVertexCount() { return m_iQuadCount * 4; }
		uint32_t GetTotalIndexCount() { return m_iQuadCount * 6; }
	}RenderStatistics;

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
		/// @brief 刷新场景
		static void RefreshScene();

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
		/// @param rTilingFactor 平铺因子
		/// @param tintColor 色调颜色
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rTilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		/// @brief 绘制四边形
		/// @param position 四边形的中心位置，使用三维向量表示（x, y, z）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param texture 2D纹理
		/// @param rTilingFactor 平铺因子
		/// @param tintColor 色调颜色
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float rTilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		/// @brief 绘制旋转四边形
		/// @param position 四边形的中心位置，使用二维向量表示（x, y）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param rRotation 旋转角度(单位: 角度)
		/// @param color 四边形的颜色，使用四维向量表示（红, 绿, 蓝, 透明度）
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rRotation, const glm::vec4& color);
		/// @brief 绘制旋转四边形
		/// @param position 四边形的中心位置，使用三维向量表示（x, y, z）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param rRotation 旋转角度(单位: 角度)
		/// @param color 四边形的颜色，使用四维向量表示（红, 绿, 蓝, 透明度）
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rRotation, const glm::vec4& color);
		/// @brief 绘制旋转四边形
		/// @param position 四边形的中心位置，使用二维向量表示（x, y）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param rRotation 旋转角度(单位: 角度)
		/// @param texture 2D纹理
		/// @param rTilingFactor 平铺因子
		/// @param tintColor 色调颜色
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rRotation, const Ref<Texture2D>& texture, float rTilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		/// @brief 绘制旋转四边形
		/// @param position 四边形的中心位置，使用三维向量表示（x, y, z）
		/// @param size 四边形的尺寸，使用二维向量表示（宽度, 高度）
		/// @param rRotation 旋转角度(单位: 角度)
		/// @param texture 2D纹理
		/// @param rTilingFactor 平铺因子
		/// @param tintColor 色调颜色
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rRotation, const Ref<Texture2D>& texture, float rTilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
	
		/// @brief 重置统计数据
		static void ResetStats();
		/// @brief 获取渲染统计数据
		/// @return 
		static RenderStatistics GetStats();

	private:
		/// @brief 刷新渲染统计数据
		static void RefreshStats();
	};

}
