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
		std::string m_sName;		//元素名称
		ShaderDataType m_enType;	//元素数据类型
		uint32_t m_nSize;			//元素数据类型字节大小
		uint32_t m_nOffset;			//偏移值
		bool m_bNormalized;			//标准化

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
		uint32_t m_nStride = 0;		//步长
	};

	/// @brief 顶点缓冲类
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		/// @brief 绑定对应顶点缓冲对象
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应顶点缓冲对象
		virtual void unBind() const = 0;

		/// @brief 设置布局
		/// @param layout 指定对象布局
		virtual void SetLayout(const BufferLayout& layout) = 0;
		
		/// @brief 获取指定对象布局
		/// @return 指定对象布局
		virtual const BufferLayout& GetLayout() const = 0;

		/// @brief 基类静态方法：创建顶点缓冲对象
		/// @param vertices 顶点属性数组
		/// @param size 顶点属性数组大小
		/// @return 返回对应RendererAPI创建的顶点缓冲对象，若无对应RendererAPI则返回空！
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	/// @brief 索引缓冲类
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		/// @brief 绑定对应索引缓冲对象
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应索引缓冲对象
		virtual void unBind() const = 0;

		/// @brief 获取索引数组大小
		/// @return 索引数组大小
		virtual uint32_t GetCount() const = 0;

		/// @brief 基类静态方法：创建索引缓冲对象
		/// @param indices 索引数组
		/// @param count 索引数组大小
		/// @return 返回对应RendererAPI创建的索引缓冲对象，若无对应RendererAPI则返回空！
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}