#pragma once
#include "Renderer/FrameBuffer.h"

namespace Echo {

	class OpenGLFrameBuffer : public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferConfiguration& configuration);
		virtual ~OpenGLFrameBuffer();

	public:
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void ReSize(uint32_t nWidth, uint32_t nHeight) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_nColorAttachment; }
		virtual const FrameBufferConfiguration& GetConfiguration() const override { return m_sConfiguration; }

	private:
		/// @brief 初始化
		void Initialize();
		/// @brief 释放相关资源
		void Release() const;

	private:
		/// @brief 帧缓冲配置
		FrameBufferConfiguration m_sConfiguration;
		/// @brief 渲染ID
		uint32_t m_RendererID = 0;
		/// @brief 颜色附件
		uint32_t m_nColorAttachment = 0;
		/// @brief 深度附件
		uint32_t m_nDepthAttachment = 0;
	};

}
