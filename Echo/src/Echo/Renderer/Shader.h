#pragma once
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 着色器类
	class Shader
	{
	public:
		virtual ~Shader() = default;

	public:
		virtual void Bind() const = 0;
		virtual void unBind() const = 0;

		/// @brief 创建着色器
		/// @param vertexSrc 顶点着色器 
		/// @param fragmentSrc 片元着色器
		/// @return 返回对应RendererAPI创建的着色器，若无对应RendererAPI则返回空！
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};

}


