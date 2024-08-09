#pragma once
#include "Camera.h"

#include "Core/Events/Event.h"
#include "Core/Events/ApplicationEvent.hpp"
#include "Core/Events/MouseEvent.hpp"
#include "Core/Events/KeyEvent.hpp"

#include "Utils/TimeStep.h"
#include "Utils/Input.h"
#include "Utils/MouseCodes.h"
#include "Utils/KeyCodes.h"

namespace Echo {

	/// @brief 编辑器视图相机: 此相机用于在编辑环境中查看和修改场景
	class EditorCamera : public Camera
	{
	public:
		/// @brief @brief 构造函数(正交相机)
		/// @param rAspectRaio 长宽比
		/// @param rZoomLevel 缩放等级
		EditorCamera(float rAspectRaio, float rZoomLevel);
		/// @brief 构造函数(透视相机)
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

		/// @brief 更新
		/// @param ts 
		void OnUpdate(TimeStep ts);
		/// @brief 处理事件
		/// @param e 
		void OnEvent(Event& e);

	public:
		/// @brief 设置投影类型
		/// @param type 
		void SetProjectionType(ProjectionType type);
		/// @brief 是否是正交投影
		/// @return 
		bool IsOrthographic() const { return m_bIsOrthographic; }

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

		/// @brief 鼠标滚轮事件
		/// @param e 
		/// @return 
		bool OnMouseScrolled(MouseScrolledEvent& e);
		/// @brief 窗口大小修改事件
		/// @param e 
		/// @return 
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		/// @brief 是否是正交投影
		bool m_bIsOrthographic = false;

		/// @brief 相机位置
		glm::vec3 m_Position = glm::vec3(0.0f);
		/// @brief 方向
		glm::vec3 m_Direction = glm::vec3(0.0f);
		/// @brief 焦点
		glm::vec3 m_FocalPoint = glm::vec3(0.0f);
		/// @brief 视图矩阵
		glm::mat4 m_ViewMat = glm::mat4(1.0f);

		/// @brief 相机长宽比
		float m_rAspectRatio;

		/* 透视相机属性 */
		/// @brief 相机视野角度(单位: 弧度)
		float m_rFovRadians = glm::radians(45.0f);
		/// @brief 透视相机近平面
		float m_rPerspectiveNear = 1.0f;
		/// @brief 透视相机远平面
		float m_rPerspectiveFar = 2000.0f;

		/* 正交相机属性 */
		/// @brief 缩放等级
		float m_rZoomLevel = 1.0f;
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

		/// @brief 偏航角（绕Y轴旋转）(单位: 弧度)
		float m_rYaw = 0.0f;
		/// @brief 俯仰角（绕X轴旋转）(单位: 弧度)
		float m_rPitch = 0.0f;

		float m_rRotation = 0.0f;
		
		/// @brief 相机到焦点的距离
		float m_rDistance = 10.0f;
		/// @brief 相机移动速度
		float m_rMoveSpeed = 5.0f;

		/// @brief 视口宽度
		uint32_t m_nViewportWidth = 1280;
		/// @brief 视口高度
		uint32_t m_nViewportHeight = 720;
	};

}
