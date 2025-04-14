#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 枚举类：着色器数据类型
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	/// @brief 获取着色器数据类型大小
	/// @param type 着色器数据类型
	/// @return 着色器数据类型大小
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

	/// @brief 缓冲元素结构体: 描述顶点数据的属性
	typedef struct ECHO_API BufferElement
	{
		/// @brief 属性名称
		std::string m_sName;
		/// @brief 属性数据类型
		ShaderDataType m_enType;
		/// @brief 属性数据类型大小
		uint32_t m_nSize;
		/// @brief 偏移量: 属性在顶点数据中的偏移量
		uint32_t m_nOffset;
		/// @brief 标准化: true-启用标准化，将整数转换为浮点数范围[0, 1]或[-1, 1]; false-不启用标准化
		bool m_bNormalized;

		BufferElement()
			:m_sName(""), m_enType(ShaderDataType::None), m_nSize(0), m_nOffset(0), m_bNormalized(false)
		{}

		BufferElement(ShaderDataType type, const std::string& elementName, bool normalized = false)
			:m_sName(elementName), m_enType(type), m_nSize(ShaderDataTypeSize(type)), m_nOffset(0), m_bNormalized(normalized)
		{
		}

		/// @brief 获取属性数据类型分量数量
		/// @return 属性数据类型分量数量
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
	}BufferElement;

	/// @brief 缓冲布局类: 用于描述顶点数据的布局
	class ECHO_API BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(const std::initializer_list<BufferElement>& elements);
		~BufferLayout() = default;

	public:
		const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		uint32_t GetStride() const { return m_nStride; }

	private:
		/// @brief 计算偏移量与步长
		void CalculateOffsetAndStride();

	private:
		/// @brief 缓冲元素列表
		std::vector<BufferElement> m_Elements;
		/// @brief 步长
		uint32_t m_nStride = 0;
	};

	/// @brief 顶点缓冲类(VBO): 用于存储顶点数据, 并且可以绑定到渲染管线中
	class ECHO_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		/// @brief 创建顶点缓冲对象
		/// @param size 顶点数组大小
		/// @return 返回对应RendererAPI创建的顶点缓冲对象，若无对应RendererAPI则返回nullptr！
		static Ref<VertexBuffer> CreateBuffer(uint32_t size);
		/// @brief 创建顶点缓冲对象
		/// @param vertices 顶点数组
		/// @param size 顶点数组大小
		/// @return 返回对应RendererAPI创建的顶点缓冲对象，若无对应RendererAPI则返回nullptr！
		static Ref<VertexBuffer> CreateBuffer(float* vertices, uint32_t size);

	public:
		/// @brief 绑定缓冲
		virtual void Bind() const = 0;
		/// @brief 解绑缓冲
		virtual void UnBind() const = 0;

		/// @brief 设置布局
		/// @param layout 布局
		virtual void SetLayout(const BufferLayout& layout) = 0;
		/// @brief 获取布局
		/// @return 布局
		virtual const BufferLayout& GetLayout() const = 0;

		/// @brief 设置顶点数据
		/// @param data 待更新的顶点数据
		/// @param size 顶点数据大小（以字节为单位）
		virtual void SetData(const void* data, uint32_t size) = 0;
	};

	/// @brief 索引缓冲类(IBO): 用于存储索引数据, 并且可以绑定到渲染管线中
	class ECHO_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		/// @brief 创建索引缓冲对象
		/// @param indeices 
		/// @param count 
		/// @return 返回对应RendererAPI创建的顶点缓冲对象，若无对应RendererAPI则返回nullptr！
		static Ref<IndexBuffer> CreateBuffer(uint32_t* indices, uint32_t count);

	public:
		/// @brief 绑定缓冲
		virtual void Bind() const = 0;
		/// @brief 解绑缓冲
		virtual void UnBind() const = 0;

		/// @brief 获取索引数组大小
		/// @return 索引数组大小
		virtual uint32_t GetCount() const = 0;
	};

}
