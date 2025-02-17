#pragma once
#include <chrono>

// deals with time and all that

namespace sglr {

    class clock {
        public:
            clock() : m_start(std::chrono::high_resolution_clock::now()) {}

            inline void restart() 
            {
                m_start = std::chrono::high_resolution_clock::now();
            }
            inline float elapsed() 
            {
                auto now = std::chrono::high_resolution_clock::now();
                return std::chrono::duration_cast<std::chrono::duration<float>>(now - m_start).count();
            }

        private:
            std::chrono::high_resolution_clock::time_point m_start;
    };
}