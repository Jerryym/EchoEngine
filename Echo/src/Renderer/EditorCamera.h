#pragma once
#include "Camera.h"

#include "Core/Events/Event.h"
#include "Core/Events/KeyEvent.hpp"
#include "Core/Events/MouseEvent.hpp"

#include "Utils/Input.h"
#include "Utils/TimeStep.h"

namespace Echo {

	/// @brief 编辑器视图相机
	class EditorCamera : public Camera
	{
	public:
		/// @brief 构造函数
		/// @param rFov 视野角度(单位：度)
		/// @param rWidth 宽度
		/// @param rHeight 高度
		/// @param rNearPlane 近平面 
		/// @param rFarPlane 远平面
		EditorCamera(float rFov, float rWidth, float rHeight, float rNearPlane, float rFarPlane);
		virtual ~EditorCamera() {}

	public:
		/// @brief 初始化
		void Initialize();

		/// @brief 
		/// @param ts 
		void OnUpdate(TimeStep ts);
		/// @brief 
		/// @param e 
		void OnEvent(Event& e);

		/// @brief 设置焦点
		/// @param focusPoint 
		void SetFocusPoint(const glm::vec3& focusPoint);
		/// @brief 获取焦点
		const glm::vec3& GetFocusPoint() const { return m_FocalPoint; }

		/// @brief 设置相机距离
		/// @param rDistance 
		void SetDistance(float rDistance);
		/// @brief 获取相机距离
		/// @return 
		float GetDistance() const { return m_rDistance; }

		/// @brief 获取视图矩阵
		/// @return 
		const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
		/// @brief 获取视图投影矩阵
		/// @return 
		glm::mat4 GetViewProjectionMatrix() const { return GetProjectionMatrix() * m_ViewMat; }

		/// @brief 设置视口大小
		/// @param width 
		/// @param height 
		void SetViewPortSize(uint32_t width, uint32_t height);

		/// @brief 获取方向
		/// @return
		glm::quat GetOrientation() const;
		/// @brief 获取向上向量
		/// @return 
		glm::vec3 GetUpDirection() const;
		/// @brief 获取向右向量
		/// @return 
		glm::vec3 GetRightDirection() const;
		/// @brief 获取向前向量
		/// @return 
		glm::vec3 GetForwardDirection() const;

	private:
		/// @brief 计算相机位置
		/// @return 相机位置
		glm::vec3 CalculatePosition() const;

		/// @brief 更新相机视图
		void UpdateCameraView();

		/// @brief 鼠标滚动事件
		/// @param e 
		/// @return 
		bool OnMouseScroll(MouseScrolledEvent& e);
		/// @brief 鼠标平移
		/// @param delta 
		void MousePan(const glm::vec2& delta);
		/// @brief 鼠标旋转
		/// @param delta 
		void MouseRotate(const glm::vec2& delta);
		/// @brief 鼠标缩放
		/// @param delta 
		void MouseZoom(float rDelta);

		/// @brief 平移速度
		/// @return 
		std::pair<float, float> PanSpeed() const;
		/// @brief 旋转速度
		/// @return 
		float RotationSpeed() const;
		/// @brief 缩放速度
		/// @return 
		float ZoomSpeed() const;

	private:
		/// @brief 相机位置
		glm::vec3 m_Position;
		/// @brief 方向
		glm::vec3 m_Direction;
		/// @brief 焦点
		glm::vec3 m_FocalPoint;
		/// @brief 视图矩阵
		glm::mat4 m_ViewMat;

		/// @brief 相机视野角度(单位: 弧度)
		float m_rFovRadians;
		/// @brief 相机长宽比
		float m_rAspectRatio;
		/// @brief 相机近平面
		float m_rNearPlane = 1.0f;
		/// @brief 相机远平面
		float m_rFarPlane = 2000.0f;

		/// @brief 偏航角（绕Y轴旋转）(单位: 弧度)
		float m_rYaw;
		/// @brief 俯仰角（绕X轴旋转）(单位: 弧度)
		float m_rPitch;
		
		/// @brief 相机到焦点的距离
		float m_rDistance = 10.0f;
		/// @brief 相机移动速度
		float m_rMoveSpeed = 2.5f;

		/// @brief 视口宽度
		uint32_t m_nViewportWidth = 1280;
		/// @brief 视口高度
		uint32_t m_nViewportHeight = 720;

		glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
	};

}
