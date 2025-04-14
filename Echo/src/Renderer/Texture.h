#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 纹理类
	class ECHO_API Texture
	{
	public:
		virtual ~Texture() = default;

	public:
		/// @brief 获取纹理宽度
		/// @return 
		virtual uint32_t GetWidth() const = 0;
		/// @brief 获取纹理高度
		/// @return 
		virtual uint32_t GetHeight() const = 0;

		/// @brief 绑定纹理
		/// @param unit 纹理单元
		virtual void Bind(uint32_t unit = 0) const = 0;
	};

	/// @brief 2D纹理类
	class ECHO_API Texture2D : public Texture
	{
	public:
		/// @brief 创建2D纹理
		/// @param sPath 2D纹理文件路径
		/// @return 返回对应RendererAPI创建的2D纹理，若无对应RendererAPI则返回nullptr！
		static Ref<Texture2D> CreateTexture(const std::string& sPath);
	};

}
