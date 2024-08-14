#pragma once
#include "Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int GLenum;

namespace Echo {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& sFilePath);
		OpenGLShader(const std::string& sShaderName, const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

	public:
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const std::string& GetName() const override { return m_sName; }

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t size) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) override;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

	public:
		//设置uniform
		void SetUniformInt(const std::string& name, int value);
		void SetUniformIntArray(const std::string& name, int* values, uint32_t size);

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& value);
		void SetUniformFloat3(const std::string& name, const glm::vec3& value);
		void SetUniformFloat4(const std::string& name, const glm::vec4& value);

		void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

		int GetUniformLocation(const std::string& name);

	private:
		/// @brief 读取着色器文件
		/// @param sFilepath 着色器文件路径
		/// @return 
		std::string ReadFile(const std::string& sFilepath);
		/// @brief 预处理着色器
		/// @param sSource 着色器源码
		/// @return
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& sSource);
		/// @brief 编译着色器
		/// @param ShaderSources 着色器源码
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);

	private:
		uint32_t m_RendererID;
		/// @brief 着色器名称
		std::string m_sName;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}

