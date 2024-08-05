#pragma once
#include "Renderer/Texture.h"

namespace Echo {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& sPath);
		virtual ~OpenGLTexture2D();

	public:
		virtual uint32_t GetWidth() const override { return m_nWidth; }
		virtual uint32_t GetHeight() const override { return m_nHeight; }
		virtual void Bind(uint32_t unit) const override;

	private:
		/// @brief 纹理文件路径
		std::string m_sPath;
		/// @brief 纹理宽度
		uint32_t m_nWidth;
		/// @brief 纹理高度
		uint32_t m_nHeight;

		uint32_t m_RendererID;
	};

}
