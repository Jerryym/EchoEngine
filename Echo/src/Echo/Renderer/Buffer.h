#pragma once

namespace Echo {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case Echo::ShaderDataType::Float:		return 4;
			case Echo::ShaderDataType::Float2:		return 4 * 2;
			case Echo::ShaderDataType::Float3:		return 4 * 3;
			case Echo::ShaderDataType::Float4:		return 4 * 4;
			case Echo::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case Echo::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case Echo::ShaderDataType::Int:			return 4;
			case Echo::ShaderDataType::Int2:		return 4 * 2;
			case Echo::ShaderDataType::Int3:		return 4 * 3;
			case Echo::ShaderDataType::Int4:		return 4 * 4;
			case Echo::ShaderDataType::Bool:		return 1;
		}

		ECHO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct BufferElement
	{
		std::string m_sName;		//Ԫ������
		ShaderDataType m_enType;	//Ԫ����������
		uint32_t m_nSize;			//Ԫ�����������ֽڴ�С
		uint32_t m_nOffset;			//ƫ��ֵ
		bool m_bNormalized;			//��׼��

		BufferElement() 
			:m_sName(""), m_enType(ShaderDataType::None), m_nSize(0), m_nOffset(0), m_bNormalized(false)
		{}

		BufferElement(ShaderDataType type, const std::string& elementName, bool normalized = false)
			:m_sName(elementName), m_enType(type), m_nSize(ShaderDataTypeSize(type)), m_nOffset(0), m_bNormalized(normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (m_enType)
			{
			case Echo::ShaderDataType::Float:		return 1;
			case Echo::ShaderDataType::Float2:		return 2;
			case Echo::ShaderDataType::Float3:		return 3;
			case Echo::ShaderDataType::Float4:		return 4;
			case Echo::ShaderDataType::Mat3:		return 3 * 3;
			case Echo::ShaderDataType::Mat4:		return 4 * 4;
			case Echo::ShaderDataType::Int:			return 1;
			case Echo::ShaderDataType::Int2:		return 2;
			case Echo::ShaderDataType::Int3:		return 3;
			case Echo::ShaderDataType::Int4:		return 4;
			case Echo::ShaderDataType::Bool:		return 1;
			}

			ECHO_CORE_ASSERT(false, "Unknown ShaderDataType!");
			return 0;
		}
	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		~BufferLayout() {}

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		uint32_t GetStride() const { return m_nStride; }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_nStride = 0;		//����
	};

	/// @brief ���㻺����
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		/// @brief �󶨶�Ӧ���㻺�����
		virtual void Bind() const = 0;
		/// @brief ����ͷŶ�Ӧ���㻺�����
		virtual void unBind() const = 0;

		/// @brief ���ò���
		/// @param layout ָ�����󲼾�
		virtual void SetLayout(const BufferLayout& layout) = 0;
		
		/// @brief ��ȡָ�����󲼾�
		/// @return ָ�����󲼾�
		virtual const BufferLayout& GetLayout() const = 0;

		/// @brief ���ྲ̬�������������㻺�����
		/// @param vertices ������������
		/// @param size �������������С
		/// @return ���ض�ӦRendererAPI�����Ķ��㻺��������޶�ӦRendererAPI�򷵻ؿգ�
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	/// @brief ����������
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		/// @brief �󶨶�Ӧ�����������
		virtual void Bind() const = 0;
		/// @brief ����ͷŶ�Ӧ�����������
		virtual void unBind() const = 0;

		/// @brief ��ȡ���������С
		/// @return ���������С
		virtual uint32_t GetCount() const = 0;

		/// @brief ���ྲ̬���������������������
		/// @param indices ��������
		/// @param count ���������С
		/// @return ���ض�ӦRendererAPI��������������������޶�ӦRendererAPI�򷵻ؿգ�
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}