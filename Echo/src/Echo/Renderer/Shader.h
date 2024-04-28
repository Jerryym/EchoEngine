#pragma once
#include <glm/glm.hpp>

namespace Echo {

	/// @brief 着色器类
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

	public:
		void Bind() const;
		void unBind() const;

		//设置uniform
		void setUniform1i(const std::string& name, int value);
		void setUniform1f(const std::string& name, float value);
		void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		int getUniformLocation(const std::string& name);

	private:
		uint32_t m_RendererID;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}


