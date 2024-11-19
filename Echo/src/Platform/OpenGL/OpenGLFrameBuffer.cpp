#include "echopch.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Echo {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferSpecification& spec)
		: m_sSpec(spec)
	{
		Initialize();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		Release();
	}

	void OpenGLFrameBuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void OpenGLFrameBuffer::UnBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::ReSize(uint32_t nWidth, uint32_t nHeight)
	{
		m_sSpec.m_nWidth = nWidth;
		m_sSpec.m_nHeight = nHeight;
		Initialize();
	}

	void OpenGLFrameBuffer::Initialize()
	{
		//若当前渲染ID不等于0，释放对应资源
		if (m_RendererID != 0)
		{
			Release();
		}

		//创建FBO
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		//给颜色缓冲创建纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &m_nColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_nColorAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_sSpec.m_nWidth, m_sSpec.m_nHeight);

		//设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//将纹理附加到FBO的颜色附件中
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_nColorAttachment, 0);

		//给深度缓冲创建纹理
		glCreateTextures(GL_TEXTURE_2D, 1, &m_nDepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_nDepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_sSpec.m_nWidth, m_sSpec.m_nHeight);

		//将纹理附加到FBO的深度附件中
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_nDepthAttachment, 0);

		ECHO_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Release() const
	{
		//释放FBO
		glDeleteFramebuffers(1, &m_RendererID);
		//释放纹理资源
		glDeleteTextures(1, &m_nColorAttachment);
		glDeleteTextures(1, &m_nDepthAttachment);
	}

}
