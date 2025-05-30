#include "echopch.h"
#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>

namespace Echo {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& sPath)
		:m_sPath(sPath)
	{
		//由于OpenGL的y轴在图片左下角，而图片的y轴一般在左上角，因此加载纹理时先翻转图片的y轴
		stbi_set_flip_vertically_on_load(1);

		int iWidth, iHeight, iChannels;
		stbi_uc* pData = stbi_load(sPath.c_str(), &iWidth, &iHeight, &iChannels, 0);
		ECHO_CORE_ASSERT(pData, "Failed to Load Image!");
		m_nWidth = iWidth;
		m_nHeight = iHeight;

		GLenum interalFormat = 0, dataFormat = 0;
		switch (iChannels)
		{
			case 3://三通道
			{
				interalFormat = GL_RGB8;
				dataFormat = GL_RGB;
				break;
			}
			case 4://四通道
			{
				interalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
				break;
			}
		}
		ECHO_CORE_ASSERT(interalFormat & dataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, interalFormat, m_nWidth, m_nHeight);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_nWidth, m_nHeight, dataFormat, GL_UNSIGNED_BYTE, pData);

		//释放图像的内存
		stbi_image_free(pData);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t unit) const
	{
		glBindTextureUnit(unit, m_RendererID);
	}

}
