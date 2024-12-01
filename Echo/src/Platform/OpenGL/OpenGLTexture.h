#pragma once
#include "Renderer/Texture.h"

#include <glad/glad.h>

namespace Echo {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& sPath);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

		virtual bool operator==(const Texture& texture) const override;

	public:
		virtual uint32_t GetWidth() const override { return m_nWidth; }
		virtual uint32_t GetHeight() const override { return m_nHeight; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t unit) const override;

	private:
		/// @brief 纹理文件路径
		std::string m_sPath;
		/// @brief 纹理宽度
		uint32_t m_nWidth;
		/// @brief 纹理高度
		uint32_t m_nHeight;
		/// @brief 渲染ID
		uint32_t m_RendererID = 0;
		/// @brief 纹理的内部数据类型
		GLenum m_InternalFormat;
		/// @brief 数据类型
		GLenum m_DataFormat;
	};

}
