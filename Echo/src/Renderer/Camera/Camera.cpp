#include "echopch.h"
#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Echo {

	Camera::Camera(const glm::mat4& projectionMat)
		: m_ProjectionMat(projectionMat)
	{
	}

	void Camera::SetProjectionMat(const glm::mat4& projectionMat)
	{
		m_ProjectionMat = projectionMat;
	}

	void Camera::SetPerspectiveProjectionMatrix(float rFov, float rWidth, float rHeight, float rNearPlane, float rFarPlane)
	{
		m_ProjectionMat = glm::perspectiveFov(rFov, rWidth, rHeight, rNearPlane, rFarPlane);
	}

	void Camera::SetOrthoProjectionMatrix(float rLeft, float rRight, float rBottom, float rTop)
	{
		m_ProjectionMat = glm::ortho(rLeft, rRight, rBottom, rTop, -1.0f, 1.0f);
	}

}
