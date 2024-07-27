#pragma once
#include "RenderCommond.h"

namespace Echo {

	/// @brief 渲染器类
	class Renderer
	{
	public:
		/// @brief 获取当前渲染API
		/// @return 
		static RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
		/// @brief 
		static void BeginScene();
		/// @brief 
		static void EndScene();
	};

}


