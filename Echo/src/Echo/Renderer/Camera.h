#pragma once
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 相机类
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);

	public:
		/// @brief 设置相机位置
		/// @param position 
		void SetPosition(const glm::vec3& position);
		/// @brief 获取相机位置
		/// @return 
		const glm::vec3& GetPosition() const { return m_Position; }
		
		/// @brief 设置旋转角度
		/// @param rotation 旋转角度（单位：角度）
		void SetRotation(float rotation);
		float GetRotation() const { return m_rRotation; }

		/// @brief 获取投影矩阵
		/// @return 
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		/// @brief 获取观察矩阵
		/// @return 
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		/// @brief 获取VP矩阵
		/// @return 
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		/// @brief 计算观察矩阵
		void CalculateViewMatrix();

	private:
		/// @brief 投影矩阵
		glm::mat4 m_ProjectionMatrix;
		/// @brief 观察矩阵
		glm::mat4 m_ViewMatrix;
		/// @brief VP矩阵
		glm::mat4 m_ViewProjectionMatrix;
		/// @brief 相机位置
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		/// @brief 旋转角度
		float m_rRotation = 0.0f;
	};

}


