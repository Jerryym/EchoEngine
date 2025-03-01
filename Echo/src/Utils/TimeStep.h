#pragma once

namespace Echo {

    /// @brief 时间步长类
    class TimeStep
    {
    public:
        TimeStep(float time = 0.0f);
        ~TimeStep() = default;

        operator float() const { return m_rTime; }

    public:
        /// @brief 获取秒
        /// @return
        float GetSeconds() const { return m_rTime; }
        /// @brief 获取毫秒
        /// @return 
        float GetMilliseconds() const { return m_rTime * 1000.0f; }

    private:
       float m_rTime;
    };

}