#pragma once

namespace Echo {

	/// @brief 时间步长
	class TimeStep
	{
	public:
		TimeStep(float time = 0.0f);
		~TimeStep() {}

		operator float() const { return m_rTime; }

	public:
		/// @brief 获取时间(单位：s)
		/// @return 
		float GetSeconds() const { return m_rTime; }
		/// @brief 获取时间(单位：ms)
		/// @return 
		float GetMilliseconds() const { return m_rTime * 1000.0f; }

	private:
		/// @brief 时间
		float m_rTime;
	};

}
