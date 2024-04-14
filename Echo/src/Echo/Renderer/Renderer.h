#pragma once

namespace Echo {

	enum class RendererAPI
	{
		None = 0, OpenGL
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI s_RendererAPI;
	};

}
