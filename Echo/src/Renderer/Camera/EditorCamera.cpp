#include "echopch.h"
#include "EditorCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Echo {

	EditorCamera::EditorCamera(float rAspectRaio, float rZoomLevel)
		: Camera(glm::ortho(-rAspectRaio * rZoomLevel, rAspectRaio * rZoomLevel, -rZoomLevel, rZoomLevel, -1.0f, 1.0f)),
		m_rAspectRatio(rAspectRaio), m_rZoomLevel(rZoomLevel),
		m_rOrthographicLeft(-rAspectRaio * rZoomLevel), m_rOrthographicRight(rAspectRaio* rZoomLevel),
		m_rOrthographicBottom(-rZoomLevel), m_rOrthographicTop(rZoomLevel),
		m_rOrthographicNear(-1.0f), m_rOrthographicFar(1.0f)
	{
		m_bIsOrthographic = true;
		SetOrthoProjectionMatrix(m_rOrthographicLeft, m_rOrthographicRight, m_rOrthographicBottom, m_rOrthographicTop);
	}

	EditorCamera::EditorCamera(float rFov, float rWidth, float rHeight, float rNearPlane, float rFarPlane)
		: Camera(glm::perspectiveFov(glm::radians(rFov), rWidth, rHeight, rNearPlane, rFarPlane)), 
		m_FocalPoint(0.0f), m_rFovRadians(glm::radians(rFov)), m_rPerspectiveNear(rNearPlane), m_rPerspectiveFar(rFarPlane)
	{
		m_bIsOrthographic = false;
		Initialize();
	}

	void EditorCamera::Initialize()
	{
		//设置相机位置
		m_Position = CalculatePosition();
		glm::quat orientation = GetOrientation();
		m_ViewMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMat = glm::inverse(m_ViewMat);
		SetPerspectiveProjectionMatrix(m_rFovRadians, (float)m_nViewportWidth, (float)m_nViewportHeight, m_rPerspectiveNear, m_rPerspectiveFar);
	}

	void EditorCamera::OnUpdate(TimeStep ts)
	{
		if (Input::IsKeyPressed(Key::KeyCode::A))				m_Position.x -= m_rMoveSpeed * ts;
		else if (Input::IsKeyPressed(Key::KeyCode::D))			m_Position.x += m_rMoveSpeed * ts;

		if (Input::IsKeyPressed(Key::KeyCode::W))				m_Position.y += m_rMoveSpeed * ts;
		else if (Input::IsKeyPressed(Key::KeyCode::S))			m_Position.y -= m_rMoveSpeed * ts;

		if (Input::IsKeyPressed(Key::KeyCode::Q))				m_rRotation += 180.f * ts;
		else if (Input::IsKeyPressed(Key::KeyCode::E))			m_rRotation -= 180.f * ts;

		UpdateCameraView();
	}

	void EditorCamera::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<MouseScrolledEvent>(BIND_EVENT(EditorCamera::OnMouseScrolled));
		dispatcher.Dispatcher<WindowResizeEvent>(BIND_EVENT(EditorCamera::OnWindowResized));
	}

	void EditorCamera::SetProjectionType(ProjectionType type)
	{
		m_bIsOrthographic = (type == ProjectionType::Orthographic) ? true : false;
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
		SetPerspectiveProjectionMatrix(m_rFovRadians, (float)m_nViewportWidth, (float)m_nViewportHeight, m_rPerspectiveNear, m_rPerspectiveFar);
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
		if (m_bIsOrthographic == false)
		{
			m_Position = CalculatePosition();
			glm::quat orientation = GetOrientation();
			m_Direction = glm::eulerAngles(orientation) * (180.0f / glm::pi<float>());
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
			m_ViewMat = glm::inverse(transform);
		}
		else
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_rRotation), glm::vec3(0, 0, 1));
			m_ViewMat = glm::inverse(transform);
		}
	}

	bool EditorCamera::OnMouseScrolled(MouseScrolledEvent& e)
	{
		if (m_bIsOrthographic == true)
		{
			m_rZoomLevel -= e.getYOffset() * 0.25f;
			m_rZoomLevel = std::max(m_rZoomLevel, 0.25f);
			SetOrthoProjectionMatrix(-m_rAspectRatio * m_rZoomLevel, m_rAspectRatio * m_rZoomLevel, -m_rZoomLevel, m_rZoomLevel);
		}
		return false;
	}

	bool EditorCamera::OnWindowResized(WindowResizeEvent& e)
	{
		if (m_bIsOrthographic == true)
		{
			m_rAspectRatio = (float)e.getWidth() / (float)e.getHeight();
			SetOrthoProjectionMatrix(-m_rAspectRatio * m_rZoomLevel, m_rAspectRatio * m_rZoomLevel, -m_rZoomLevel, m_rZoomLevel);
		}
		return false;
	}

}
