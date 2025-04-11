#pragma once
#include <Core.h>
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 投影类型
	enum class ECHO_API ProjectionType
	{
		/// @brief 透视
		Perspective = 0,
		/// @brief 正交
		Orthographic
	};

	/// @brief 相机类
	class ECHO_API Camera
	{
	public:
		Camera() = default;
		Camera(ProjectionType type, const glm::mat4& projectionMat);
		virtual ~Camera() = default;

	public:
		/// @brief 设置相机投影类型
		/// @param type 
		void SetProjectionType(ProjectionType type);
		/// @brief 获取相机投影类型
		/// @return 
		ProjectionType GetProjectionType() const { return m_enType; }

		/// @brief 设置相机位置
		/// @param position 
		void SetPosition(const glm::vec3& position);
		/// @brief 获取相机位置
		/// @return 
		const glm::vec3 GetPosition() const { return m_Position; }
		/// @brief 设置相机方向(目标点)
		/// @param direction 
		void SetDirection(const glm::vec3& direction);
		/// @brief 获取相机方向
		/// @return 
		const glm::vec3 GetDirection() const { return m_Direction; }
		/// @brief 设置相机的向上向量
		/// @param up 
		void SetUpVector(const glm::vec3& up);
		/// @brief 获取相机的向上向量
		/// @return 
		const glm::vec3 GetUpVector() const { return m_UpVector; }

		/// @brief 设置相机投影矩阵
		/// @param projectionMat 
		void SetProjectionMat(const glm::mat4& projectionMat);
		/// @brief 获取相机投影矩阵
		/// @return 
		const glm::mat4 GetProjectionMat() const { return m_ProjectionMat; }

		/// @brief 获取视图矩阵
		/// @return 
		glm::mat4 GetViewMat() const;
		/// @brief 获取视图投影矩阵
		/// @return 
		glm::mat4 GetViewProjectionMatrix() const;

		/// @brief 设置透视投影矩阵
		/// @param fov 视野角度(单位: 弧度)
		/// @param width 宽度
		/// @param height 高度
		/// @param nearPlane 近平面
		/// @param farPlane 远平面
		void SetPerspectiveMat(float fov, float width, float height, float nearPlane, float farPlane);
		/// @brief 设置正交投影矩阵
		/// @param left 
		/// @param right 
		/// @param bottom 
		/// @param top 
		void SetOrthoMat(float left, float right, float bottom, float top);

	private:
		/// @brief 投影类型
		ProjectionType m_enType = ProjectionType::Perspective;

		/// @brief 相机位置
		glm::vec3 m_Position = glm::vec3(0.0f);
		/// @brief 相机朝向
		glm::vec3 m_Direction = glm::vec3(0.0f);
		/// @brief 向上向量
		glm::vec3 m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);

		/// @brief 投影矩阵
		glm::mat4 m_ProjectionMat = glm::mat4(1.0f);
	};

}
