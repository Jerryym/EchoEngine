#include "echopch.h"
#include "SceneCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Echo {

	SceneCamera::SceneCamera(ProjectionType enType)
		: m_enType(enType)
	{
		RecalculateProjection();
	}

	void SceneCamera::SetProjectionType(ProjectionType type)
	{
		m_enType = type;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_rAspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float rWidth, float rHeight, float rSize, float rNear, float rFar)
	{
		m_enType = ProjectionType::Orthographic;
		m_rOrthographicSize = rSize;
		m_rAspectRatio = rWidth / rHeight;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicSize(float rSize)
	{
		m_rOrthographicSize = rSize;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicNearClip(float rNear)
	{
		m_rOrthographicNear = rNear;
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographicFarClip(float rFar)
	{
		m_rOrthographicFar = rFar;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspective(float rFov, float rAspectRatio, float rNear, float rFar)
	{
		m_enType = ProjectionType::Perspective;
		m_rPerspectiveFov = rFov;
		m_rAspectRatio = rAspectRatio;
		m_rPerspectiveNear = rNear;
		m_rPerspectiveFar = rFar;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveFOV(float rFov)
	{
		m_rPerspectiveFov = rFov;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveNearClip(float rNear)
	{
		m_rPerspectiveNear = rNear;
		RecalculateProjection();
	}

	void SceneCamera::SetPerspectiveFarClip(float rFar)
	{
		m_rPerspectiveFar = rFar;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (m_enType == ProjectionType::Perspective)//透视
		{
			m_ProjectionMat = glm::perspective(m_rPerspectiveFov, m_rAspectRatio, m_rPerspectiveNear, m_rPerspectiveFar);
		}
		else//正交
		{
			m_rOrthographicLeft = m_rOrthographicSize * m_rAspectRatio * 0.5f;
			m_rOrthographicRight = m_rOrthographicSize * m_rAspectRatio * 0.5f;
			m_rOrthographicBottom = -m_rOrthographicSize * 0.5f;
			m_rOrthographicTop = m_rOrthographicSize * 0.5f;
			m_ProjectionMat = glm::ortho(m_rOrthographicLeft, m_rOrthographicRight, m_rOrthographicBottom, m_rOrthographicTop, m_rOrthographicNear, m_rOrthographicFar);
		}
	}

}
