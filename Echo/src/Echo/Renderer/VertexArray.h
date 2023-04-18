#pragma once
#include <memory>
#include "Buffer.h"

namespace Echo {

	/// @brief 顶点数组
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		/// @brief 绑定对应顶点数组
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应顶点数组
		virtual void unBind() const = 0;

		/// @brief 添加顶点缓冲对象
		/// @param vertexbuffer 顶点缓冲对象
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) = 0;
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// @brief 设置索引缓冲对象
		/// @param indexbuffer 索引缓冲对象
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		/// @brief 基类静态方法：创建顶点数组
		/// @return 返回对应RendererAPI创建的顶点数组，若无对应RendererAPI则返回空！
		static VertexArray* Create();
	};

}

