#pragma once
#include "Camera.h"

namespace Echo {

	/// @brief 场景相机类
	class SceneCamera : public Camera
	{
	public:
		/// @brief 投影类型
		enum ProjectionType
		{
			Perspective = 0, Orthographic
		};

	public:
		SceneCamera() {}
		SceneCamera(ProjectionType enType);
		virtual ~SceneCamera() {}

	public:
		/// @brief 设置投影类型
		/// @param type 
		void SetProjectionType(ProjectionType type);
		/// @brief 获取投影类型
		/// @return 
		ProjectionType GetProjectionType() const { return m_enType; }

		/// @brief 设置视口大小
		/// @param width 
		/// @param height 
		void SetViewportSize(uint32_t width, uint32_t height);

		/////////////////////////////////////////////////
		//正交相机功能函数/////////////////////////////////
		/////////////////////////////////////////////////
		/// @brief 设计正交相机
		/// @param width 正交相机宽度
		/// @param height 正交相机高度
		/// @param size 视口大小
		/// @param near 正交相机近端面
		/// @param far 正交相机远端面
		void SetOrthographic(float rWidth, float rHeight, float rSize, float rNear = -1.0f, float rFar = 1.0f);
		
		/// @brief 设置正交相机视口大小
		/// @param size 
		void SetOrthographicSize(float rSize);
		/// @brief 获取正交相机视口大小
		/// @return 
		float GetOrthographicSize() const { return m_rOrthographicSize; }

		/// @brief 设置正交相机近端面
		/// @param near 
		void SetOrthographicNearClip(float rNear);
		float GetOrthographicNearClip() const { return m_rOrthographicNear; }
		/// @brief 设置正交相机远端面
		/// @param far 
		void SetOrthographicFarClip(float rFar);
		float GetOrthographicFarClip() const { return m_rOrthographicFar; }

		/////////////////////////////////////////////////
		//透视相机功能函数/////////////////////////////////
		/////////////////////////////////////////////////
		/// @brief 设计透视相机
		/// @param fov 透视相机垂直视野角度
		/// @param aspectRatio 透视相机长宽比
		/// @param near 透视相机近端面
		/// @param far 透视相机体远端面
		void SetPerspective(float rFov, float rAspectRatio, float rNear, float rFar);

		/// @brief 设置透视相机视野角度
		/// @param fov 
		void SetPerspectiveFOV(float rFov);
		float GetPerspectiveFOV() const { return m_rPerspectiveFov; }

		/// @brief 设置透视相机近端面
		/// @param near 
		void SetPerspectiveNearClip(float rNear);
		float GetPerspectiveNearClip() const { return m_rPerspectiveNear; }
		/// @brief 设置透视相机远端面
		/// @param far 
		void SetPerspectiveFarClip(float rFar);
		float GetPerspectiveFarClip() const { return m_rPerspectiveFar; }

	private:
		/// @brief 计算投影矩阵
		void RecalculateProjection();

	private:
		/// @brief 投影类型
		ProjectionType m_enType = ProjectionType::Orthographic;

		/////////////////////////////////////////////////
		//正交相机参数////////////////////////////////////
		/////////////////////////////////////////////////
		/// @brief 正交相机视口大小
		float m_rOrthographicSize = 10.0f;
		/// @brief 正交相机左侧面，右侧面
		float m_rOrthographicLeft = 0.0f, m_rOrthographicRight = 800.0f;
		/// @brief 正交相机下底面，上底面
		float m_rOrthographicBottom = 0.0f, m_rOrthographicTop = 600.0f;
		/// @brief 正交相机近平面
		float m_rOrthographicNear = -1.0f;
		/// @brief 正交相机远平面
		float m_rOrthographicFar = 1.0f;

		/////////////////////////////////////////////////
		//投影相机参数////////////////////////////////////
		/////////////////////////////////////////////////
		/// @brief 透视相机视野角度
		float m_rPerspectiveFov = glm::radians(45.0f);
		/// @brief 透视相机长宽比
		float m_rAspectRatio = 0.0f;
		/// @brief 透视相机近平面
		float m_rPerspectiveNear = 1.0f;
		/// @brief 透视相机远平面
		float m_rPerspectiveFar = 2000.0f;
	};

}


