#include "echopch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Echo {

	static GLenum ShaderTypeFromString(const std::string& sType)
	{
		//顶点着色器
		if (sType == "vertex")
		{
			return GL_VERTEX_SHADER;
		}

		//片元着色器
		if (sType == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}
		ECHO_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& sFilePath)
	{
		std::string sSources = ReadFile(sFilePath);
		auto ShaderSources = PreProcess(sSources);
		Compile(ShaderSources);

		//获取着色器名称: 文件名(无后缀)
		std::filesystem::path file(sFilePath);
		m_sName = file.stem().string();
	}

	OpenGLShader::OpenGLShader(const std::string& sShaderName, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_sName(sShaderName)
	{
		std::unordered_map<GLenum, std::string> ShaderSources;
		ShaderSources[GL_VERTEX_SHADER] = vertexSrc;
		ShaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(ShaderSources);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		int iLocation = GetUniformLocation(name);
		glUniform1i(iLocation, value);
	}

	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		int iLocation = GetUniformLocation(name);
		glUniform1f(iLocation, value);
	}

	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		int iLocation = GetUniformLocation(name);
		glUniform2f(iLocation, value.x, value.y);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		int iLocation = GetUniformLocation(name);
		glUniform3f(iLocation, value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		int iLocation = GetUniformLocation(name);
		glUniform4f(iLocation, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
	{
		int iLocation = GetUniformLocation(name);
		glUniformMatrix3fv(iLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		int iLocation = GetUniformLocation(name);
		glUniformMatrix4fv(iLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
		{
			ECHO_CLIENT_ERROR("[Warning]: uniform {0} doesn't exist!", name);
		}

		m_UniformLocationCache[name] = location;
		return location;
	}

	std::string OpenGLShader::ReadFile(const std::string& sFilepath)
	{
		std::string result;
		std::ifstream in(sFilepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			ECHO_CORE_ERROR("Could not open file '{0}'", sFilepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& sSource)
	{
		std::unordered_map<GLenum, std::string> ShaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = sSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = sSource.find_first_of("\r\n", pos);
			ECHO_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = sSource.substr(begin, eol - begin);
			ECHO_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = sSource.find_first_not_of("\r\n", eol);
			pos = sSource.find(typeToken, nextLinePos);
			ShaderSources[ShaderTypeFromString(type)] = sSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? sSource.size() - 1 : nextLinePos));
		}
		return ShaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
	{
		GLuint program = glCreateProgram();
		ECHO_CORE_ASSERT(ShaderSources.size() <= 2, "We only support 2 shaders for now");

		std::array<GLenum, 2> glShaderIDs;
		int iIndex = 0;
		for (auto& item : ShaderSources)
		{
			GLenum type = item.first;
			std::string sSource = item.second;

			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = sSource.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				ECHO_CORE_ERROR("{0}", infoLog.data());
				ECHO_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}
			glAttachShader(program, shader);
			glShaderIDs[iIndex++] = shader;
		}
		m_RendererID = program;

		// Link program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);

			for (auto id : glShaderIDs)
			{
				glDeleteShader(id);
			}

			ECHO_CORE_ERROR("{0}", infoLog.data());
			ECHO_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
		}
	}

}
