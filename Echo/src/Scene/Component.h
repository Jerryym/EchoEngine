#pragma once
#include "Core.h"

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace Echo {

	/// @brief 变换组件
	struct ECHO_API TransformComponent
	{
		/// @brief 坐标
		glm::vec3 position = glm::vec3(0.0f);
		/// @brief 旋转(单位: 弧度)
		glm::vec3 rotation = glm::vec3(0.0f);
		/// @brief 缩放
		glm::vec3 scale = glm::vec3(1.0f);

		/// @brief 获取变换矩阵
		/// @return 
		glm::mat4 GetTransformMat() const
		{
			glm::mat4 transMat = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 rotationMat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
			glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
			return transMat * rotationMat * scaleMat;
		}

	};

}
