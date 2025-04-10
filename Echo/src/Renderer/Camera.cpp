#include "echopch.h"
#include "Camera.h"

#include <glm/ext/matrix_clip_space.hpp>

namespace Echo {

	Camera::Camera(ProjectionType type, const glm::mat4& projectionMat)
		: m_enType(type), m_ProjectionMat(projectionMat)
	{
	}

	void Camera::SetProjectionType(ProjectionType type)
	{
		m_enType = type;
	}

	void Camera::SetProjectionMat(const glm::mat4& projectionMat)
	{
		m_ProjectionMat = projectionMat;
	}

	void Camera::SetPerspectiveMat(float fov, float width, float height, float nearPlane, float farPlane)
	{
		m_ProjectionMat = glm::perspectiveFov(fov, width, height, nearPlane, farPlane);
	}

	void Camera::SetOrthoMat(float left, float right, float bottom, float top)
	{
		m_ProjectionMat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	}

}
