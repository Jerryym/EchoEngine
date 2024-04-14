#pragma once

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

	private:
		uint32_t m_RendererID;
	};

}


