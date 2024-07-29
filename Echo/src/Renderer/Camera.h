#pragma once
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 相机类
	class Camera
	{
	public:
		Camera() {}
		Camera(const glm::mat4& projectionMat) : m_ProjectionMat(projectionMat) {}
		virtual ~Camera() {}

	public:
		/// @brief 获取投影矩阵
		/// @return 
		const glm::mat4 GetProjectcionMat() const { return m_ProjectionMat; }

	protected:
		/// @brief 投影矩阵
		glm::mat4 m_ProjectionMat = glm::mat4(1.0f);
	};

}
