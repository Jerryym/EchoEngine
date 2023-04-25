#pragma once
#include <memory>
#include "Buffer.h"

namespace Echo {

	/// @brief ��������
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		/// @brief �󶨶�Ӧ��������
		virtual void Bind() const = 0;
		/// @brief ����ͷŶ�Ӧ��������
		virtual void unBind() const = 0;

		/// @brief ��Ӷ��㻺�����
		/// @param vertexbuffer ���㻺�����
		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexbuffer) = 0;
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;

		/// @brief ���������������
		/// @param indexbuffer �����������
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		/// @brief ���ྲ̬������������������
		/// @return ���ض�ӦRendererAPI�����Ķ������飬���޶�ӦRendererAPI�򷵻ؿգ�
		static VertexArray* Create();
	};

}

