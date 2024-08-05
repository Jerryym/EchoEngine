#pragma once
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 相机类
	class Camera
	{
	public:
		Camera() {}
		Camera(const glm::mat4& projectionMat);
		virtual ~Camera() {}

	public:
		/// @brief 设置投影矩阵
		/// @param projectionMat 
		void SetProjectionMat(const glm::mat4& projectionMat);
		/// @brief 获取投影矩阵
		/// @return 
		const glm::mat4 GetProjectionMatrix() const { return m_ProjectionMat; }

		/// @brief 设置透视投影矩阵
		/// @param rFov 视野角度(单位: 弧度)
		/// @param rWidth 宽度
		/// @param rHeight 高度
		/// @param rNearPlane 近平面 
		/// @param rFarPlane 远平面
		void SetPerspectiveProjectionMatrix(float rFov, float rWidth, float rHeight, float rNearPlane, float rFarPlane);
		/// @brief 设置正交投影矩阵
		/// @param rWidth 宽度
		/// @param rHeight 高度
		/// @param rNearPlane 近平面 
		/// @param rFarPlane 远平面
		void SetOrthoProjectionMatrix(float rWidth, float rHeight, float rNearPlane, float rFarPlane);

	protected:
		/// @brief 投影矩阵
		glm::mat4 m_ProjectionMat = glm::mat4(1.0f);
	};

}
