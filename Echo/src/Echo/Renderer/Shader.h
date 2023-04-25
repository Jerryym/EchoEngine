#pragma once

namespace Echo {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void unBind() const;

	private:
		uint32_t m_RendererID;
	};

}


