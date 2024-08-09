#include "echopch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

namespace Echo {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& sPath)
		: m_sPath(sPath)
	{
		int iWidth, iHeight, iChannels;
		//由于OpenGL的y轴在图片左下角，而图片的y轴一般在左上角，因此加载纹理时先翻转图片的y轴
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* pData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);
		ECHO_CORE_ASSERT(pData, "Failed to Load Image!");
		m_nWidth = iWidth;
		m_nHeight = iHeight;

		GLenum internalFormat = 0, dataFormat = 0;
		if (iChannels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (iChannels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_nWidth, m_nHeight);

		//设置纹理过滤方式
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//设置纹理X、Y方向循环使用纹理
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_nWidth, m_nHeight, GL_RGB, GL_UNSIGNED_BYTE, pData);

		//释放图像的内存
		stbi_image_free(pData);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_nWidth(width), m_nHeight(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_nWidth, m_nHeight);

		//设置纹理过滤方式
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//设置纹理X、Y方向循环使用纹理
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		ECHO_CORE_ASSERT(size == m_nWidth * m_nHeight * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_nWidth, m_nHeight, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::Bind(uint32_t unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

}
