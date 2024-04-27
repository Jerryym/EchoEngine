#pragma once
#include <Echo/EngineCore.h>

namespace Echo {

	/// @brief 着色器数据类型
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

	/// @brief 缓冲元素属性
	struct BufferElement
	{
		/// @brief 元素名称
		std::string m_sName;
		/// @brief 元素数据类型
		ShaderDataType m_enType;
		/// @brief 元素数据类型字节大小
		uint32_t m_nSize;
		/// @brief 偏移值
		uint32_t m_nOffset;
		/// @brief 归一化
		bool m_bNormalized;

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

	/// @brief 缓冲布局类
	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		~BufferLayout() {}

	public:
		/// @brief 获取缓冲元素数组
		/// @return 
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		/// @brief 获取步幅
		/// @return 
		uint32_t GetStride() const { return m_nStride; }

	private:
		/// @brief 计算偏移量和步幅
		void CalculateOffsetAndStride();

	private:
		/// @brief 缓冲元素数组
		std::vector<BufferElement> m_Elements;
		/// @brief 步幅
		uint32_t m_nStride = 0;
	};

	/// @brief 顶点缓冲类
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

	public:
		/// @brief 绑定对应顶点缓冲对象
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应顶点缓冲对象
		virtual void UnBind() const = 0;

		/// @brief 设置布局
		/// @param layout 指定对象布局
		virtual void SetLayout(const BufferLayout& layout) = 0;
		/// @brief 获取指定对象布局
		/// @return 指定对象布局
		virtual const BufferLayout& GetLayout() const = 0;

		/// @brief 创建顶点缓冲对象(VBO)
		/// @param vertices 顶点数组
		/// @param size 顶点数组大小
		/// @return 
		static VertexBuffer* Create(float* vertices, uint32_t size);

	};

	/// @brief 索引缓冲类
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

	public:
		/// @brief 绑定对应顶点缓冲对象
		virtual void Bind() const = 0;
		/// @brief 解绑释放对应顶点缓冲对象
		virtual void UnBind() const = 0;

		/// @brief 获取索引数组大小
		/// @return 索引数组大小
		virtual uint32_t GetCount() const = 0;

		/// @brief 创建索引缓冲对象(IBO)
		/// @param indices 索引数组
		/// @param size 索引数组大小
		/// @return 
		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}

