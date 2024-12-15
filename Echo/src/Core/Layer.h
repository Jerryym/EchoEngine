#pragma once
#include "Core.h"

namespace Echo {

	/// @brief 层类
	class ECHO_API Layer
	{
	public:
		Layer(const std::string& sLayerName);
		virtual ~Layer() {}

	public:
		/// @brief 获取层名称
		/// @return 
		const std::string& GetName() const { return m_sLayerName; }

	private:
		/// @brief 层名称
		std::string m_sLayerName;
	};

}
