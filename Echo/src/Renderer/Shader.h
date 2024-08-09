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
		virtual void UnBind() const = 0;

		/// @brief 获取着色器名称
		/// @return 
		virtual const std::string& GetName() const = 0;

		/// @brief 创建着色器
		/// @param sFilePath 着色器路径 
		/// @return 返回对应RendererAPI创建的着色器，若无对应RendererAPI则返回nullptr！
		static Ref<Shader> Create(const std::string& sFilePath);
		/// @brief 创建着色器
		/// @param sShaderName 着色器名称
		/// @param vertexSrc 顶点着色器 
		/// @param fragmentSrc 片元着色器
		/// @return 返回对应RendererAPI创建的着色器，若无对应RendererAPI则返回nullptr！
		static Ref<Shader> Create(const std::string& sShaderName, const std::string& vertexSrc, const std::string& fragmentSrc);

	public:
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
	};

	/// @brief 着色器库
	class ShaderLibrary
	{
	public:
		/// @brief 添加着色器
		/// @param sName 着色器名称
		/// @param shader 着色器对象
		void Add(const std::string& sName, const Ref<Shader>& shader);
		/// @brief 添加着色器
		/// @param shader 着色器对象
		void Add(const Ref<Shader>& shader);

		/// @brief 加载着色器
		/// @param sFilepath 着色器文件路径
		/// @return 指定文件路径的着色器
		Ref<Shader> Load(const std::string& sFilepath);
		/// @brief 加载着色器
		/// @param sName 着色器名称
		/// @param sFilepath 着色器文件路径
		/// @return 指定名称着色器
		Ref<Shader> Load(const std::string& sName, const std::string& sFilepath);

		/// @brief 根据名称获取着色器
		/// @param sName 着色器名称
		/// @return 
		Ref<Shader> Get(const std::string& sName);

	private:
		/// @brief 判断着色器是否存在
		/// @param sName 着色器名称 
		/// @return 
		bool Exists(const std::string& sName) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}


