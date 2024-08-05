#pragma once
#include "Buffer.h"

namespace Echo {

	/// @brief 顶点数组类
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		/// @brief 创建顶点数组
		/// @return 返回对应RendererAPI创建的顶点数组，若无对应RendererAPI则返回nullptr！
		static VertexArray* CreateVertexArray();

	public:
		/// @brief 绑定对应顶点数组
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应顶点数组
		virtual void UnBind() const = 0;

		/// @brief 添加顶点缓冲对象
		/// @param vertexbuffer 顶点缓冲对象
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// @brief 设置索引缓冲对象
		/// @param indexbuffer 索引缓冲对象
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer) = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
	};

}

