#include "echopch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
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

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void Camera::SetDirection(const glm::vec3& direction)
	{
		m_Direction = direction;
	}

	void Camera::SetUpVector(const glm::vec3& up)
	{
		m_UpVector = up;
	}

	void Camera::SetProjectionMat(const glm::mat4& projectionMat)
	{
		m_ProjectionMat = projectionMat;
	}

	glm::mat4 Camera::GetViewMat() const
	{
		glm::mat4 viewMat = glm::lookAt(m_Position, m_Direction, m_UpVector);
		return viewMat;
	}

	glm::mat4 Camera::GetViewProjectionMatrix() const
	{
		return m_ProjectionMat * GetViewMat();
	}

	void Camera::SetPerspectiveMat(float fov, float width, float height, float nearPlane, float farPlane)
	{
		m_ProjectionMat = glm::perspectiveFov(fov, width, height, nearPlane, farPlane);
		m_enType = ProjectionType::Perspective;
	}

	void Camera::SetOrthoMat(float left, float right, float bottom, float top)
	{
		m_ProjectionMat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_enType = ProjectionType::Orthographic;
	}

}
