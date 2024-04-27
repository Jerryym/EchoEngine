#include "echopch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Echo {

	Camera::Camera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateViewMatrix();
	}

	void Camera::SetRotation(float rotation)
	{
		m_rRotation = rotation;
		CalculateViewMatrix();
	}

	void Camera::CalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rRotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}
