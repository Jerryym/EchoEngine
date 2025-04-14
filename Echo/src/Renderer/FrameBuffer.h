#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 帧缓冲配置
	typedef struct FrameBufferConfiguration
	{
		/// @brief 宽度
		uint32_t m_nWidth;
		/// @brief 高度
		uint32_t m_nHeight;
		/// @brief 是否为缓冲交换链目标
		bool m_bSwapChainTarget = false;
	} FrameBufferConfiguration;


	class ECHO_API FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		/// @brief 创建帧缓冲
		/// @param configuration 帧缓冲配置 
		/// @return 返回对应RendererAPI创建的帧缓冲对象，若无对应RendererAPI则返回nullptr！
		static Ref<FrameBuffer> CreateBuffer(const FrameBufferConfiguration& configuration);

	public:
		/// @brief 绑定
		virtual void Bind() const = 0;
		/// @brief 解绑
		virtual void UnBind() const = 0;

		/// @brief 重置帧缓冲大小
		/// @param nWidth 
		/// @param nHeight 
		virtual void ReSize(uint32_t nWidth, uint32_t nHeight) = 0;

		/// @brief 获取颜色附件渲染ID
		/// @return 
		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		/// @brief 获取帧缓冲配置对象
		/// @return 
		virtual const FrameBufferConfiguration& GetConfiguration() const = 0;
	};

}
