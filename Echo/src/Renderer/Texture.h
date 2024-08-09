#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 纹理类: 此类为抽象类，具体实现类由子类实现
	class Texture
	{
	public:
		virtual ~Texture() {}

	public:
		/// @brief 获取纹理宽度
		/// @return 
		virtual uint32_t GetWidth() const = 0;
		/// @brief 获取纹理高度
		/// @return 
		virtual uint32_t GetHeight() const = 0;

		/// @brief 设置纹理数据
		/// @param data 纹理数据
		/// @param size 数据大小
		virtual void SetData(void* data, uint32_t size) = 0;

		/// @brief 绑定纹理
		/// @param unit 纹理单元
		virtual void Bind(uint32_t unit = 0) const = 0;
	};

	/// @brief 2D纹理类
	class Texture2D : public Texture
	{
	public:
		/// @brief 创建2D纹理
		/// @param sPath 2D纹理文件路径
		/// @return 返回对应RendererAPI创建的2D纹理，若无对应RendererAPI则返回nullptr！
		static Ref<Texture2D> CreateTexture(const std::string& sPath);
		/// @brief 创建2D纹理
		/// @param width 纹理宽度
		/// @param height 纹理高度
		/// @return 返回对应RendererAPI创建的2D纹理，若无对应RendererAPI则返回nullptr！
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
	};

}
