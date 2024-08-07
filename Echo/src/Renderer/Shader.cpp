#include "echopch.h"
#include "Shader.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Echo {

	/////////////////////////////////////////////////////
	// Shader ///////////////////////////////////////////
	/////////////////////////////////////////////////////
	Ref<Shader> Shader::Create(const std::string& sFilePath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(sFilePath);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& sShaderName, const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				ECHO_CORE_ASSERT(false, "RendererAPI::None is currently not sopported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(sShaderName, vertexSrc, fragmentSrc);
		}
		ECHO_CORE_ASSERT(false, "Unkown RendererAPI!");
		return nullptr;
	}

	/////////////////////////////////////////////////////
	// ShaderLibrary ////////////////////////////////////
	/////////////////////////////////////////////////////
	void ShaderLibrary::Add(const std::string& sName, const Ref<Shader>& shader)
	{
		ECHO_CORE_ASSERT(!Exists(sName), "Shader already exists!");
		m_Shaders[sName] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& sFilepath)
	{
		auto shader = Shader::Create(sFilepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& sName, const std::string& sFilepath)
	{
		auto shader = Shader::Create(sFilepath);
		Add(sName, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& sName)
	{
		ECHO_CORE_ASSERT(Exists(sName), "Shader not found!");
		return m_Shaders[sName];
	}

	bool ShaderLibrary::Exists(const std::string& sName) const
	{
		return m_Shaders.find(sName) != m_Shaders.end();
	}

}
