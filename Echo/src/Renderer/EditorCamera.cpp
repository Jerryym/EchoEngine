#include "echopch.h"
#include "EditorCamera.h"

#include "Utils/MouseCodes.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Echo {

	EditorCamera::EditorCamera(float rFov, float rWidth, float rHeight, float rNearPlane, float rFarPlane)
		: Camera(glm::perspectiveFov(glm::radians(rFov), rWidth, rHeight, rNearPlane, rFarPlane)), 
		m_FocalPoint(0.0f), m_rFovRadians(glm::radians(rFov)), m_rNearPlane(rNearPlane), m_rFarPlane(rFarPlane)
	{
		Initialize();
	}

	void EditorCamera::Initialize()
	{
		//设置相机位置
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_ViewMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMat = glm::inverse(m_ViewMat);
		SetPerspectiveProjectionMatrix(m_rFovRadians, (float)m_nViewportWidth, (float)m_nViewportHeight, m_rNearPlane, m_rFarPlane);
	}

	void EditorCamera::OnUpdate(TimeStep ts)
	{
		const glm::vec2& mouse{ Input::GetMouseX(), Input::GetMouseY() };
		glm::vec2 delta = (mouse - m_InitialMousePosition) * 0.003f;
		m_InitialMousePosition = mouse;

		if (Input::IsMouseButtonPressed(ECHO_MOUSE_BUTTON_MIDDLE))
		{
			MousePan(delta);
		}
		else if (Input::IsMouseButtonPressed(ECHO_MOUSE_BUTTON_LEFT))
		{
			MouseRotate(delta);
		}
		else if (Input::IsMouseButtonPressed(ECHO_MOUSE_BUTTON_RIGHT))
		{
			MouseZoom(delta.y);
		}
		UpdateCameraView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<MouseScrolledEvent>(BIND_EVENT(EditorCamera::OnMouseScroll));
	}

	void EditorCamera::SetFocusPoint(const glm::vec3& focusPoint)
	{
		m_FocalPoint = focusPoint;
	}

	void EditorCamera::SetDistance(float rDistance)
	{
		m_rDistance = rDistance;
	}

	void EditorCamera::SetViewPortSize(uint32_t width, uint32_t height)
	{
		if (m_nViewportWidth == width && m_nViewportHeight == height)
		{
			return;
		}
		m_nViewportWidth = width;
		m_nViewportHeight = height;
		SetPerspectiveProjectionMatrix(m_rFovRadians, (float)m_nViewportWidth, (float)m_nViewportHeight, m_rNearPlane, m_rFarPlane);
	}

	glm::quat EditorCamera::GetOrientation() const
	{
		return glm::quat(glm::vec3(-m_rPitch, -m_rYaw, 0.0f));
	}

	glm::vec3 EditorCamera::GetUpDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetRightDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	glm::vec3 EditorCamera::GetForwardDirection() const
	{
		return glm::rotate(GetOrientation(), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 EditorCamera::CalculatePosition() const
	{
		return m_FocalPoint - GetForwardDirection() * m_rDistance;
	}

	void EditorCamera::UpdateCameraView()
	{
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_Direction = glm::eulerAngles(orientation) * (180.0f / glm::pi<float>());
		m_ViewMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMat = glm::inverse(m_ViewMat);
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& e)
	{
		float rDelta = e.getYOffset() * 0.1f;
		MouseZoom(rDelta);
		UpdateCameraView();
		return false;
	}

	void EditorCamera::MousePan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed();
		m_FocalPoint += -GetRightDirection() * delta.x * xSpeed * m_rDistance;
		m_FocalPoint += GetUpDirection() * delta.y * ySpeed * m_rDistance;
	}

	void EditorCamera::MouseRotate(const glm::vec2& delta)
	{
		float yawSign = GetUpDirection().y < 0 ? -1.0f : 1.0f;
		m_rYaw += yawSign * delta.x * RotationSpeed();
		m_rPitch += delta.y * RotationSpeed();
	}

	void EditorCamera::MouseZoom(float rDelta)
	{
		m_rDistance -= rDelta * ZoomSpeed();
		if (m_rDistance < 1.0f)
		{
			m_FocalPoint += GetForwardDirection();
			m_rDistance = 1.0f;
		}
	}

	std::pair<float, float> EditorCamera::PanSpeed() const
	{
		float x = std::min((float)m_nViewportWidth / 1000.0f, 2.4f); // max = 2.4f
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = std::min((float)m_nViewportHeight / 1000.0f, 2.4f); // max = 2.4f
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	float EditorCamera::RotationSpeed() const
	{
		return 0.8f;
	}

	float EditorCamera::ZoomSpeed() const
	{
		float rDistance = m_rDistance * 0.2f;
		rDistance = std::max(rDistance, 0.0f);
		float rSpeed = rDistance * rDistance;
		rSpeed = std::min(rSpeed, 100.0f); // max speed = 100
		return rSpeed;
	}

}
