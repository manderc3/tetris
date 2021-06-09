#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace Time
{   
    template<typename TimeType, typename T = int>
    class Timer
    {
    public:
    Timer(const T interval) : m_interval(interval) {};

    void begin()
    {
	m_time_point = std::chrono::steady_clock::now();
	m_ticking = true;
    }

    void stop()
    {
	m_ticking = false;
    }

    const bool duration_elapsed() const
    {  
	return std::chrono::duration_cast<TimeType>(std::chrono::steady_clock::now() - m_time_point).count() > m_interval;
    }

    const bool has_started() const
    {
	return m_ticking;
    }

    private:
    std::chrono::time_point<std::chrono::steady_clock> m_time_point;

    const T m_interval;

    bool m_ticking = false;
    };
}

#endif
