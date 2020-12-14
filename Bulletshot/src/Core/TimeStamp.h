#pragma once

#include <chrono>

class TimeStamp
{
public:
    TimeStamp()
        : begin(clock::now())
    {}

    // Restart timer to current time
    void Restart() { begin = clock::now(); }

    // Get delta time as seconds
    float Elapsed() const { return std::chrono::duration_cast<second>(clock::now() - begin).count(); }

    // Using as seed by randomizer
    static uint32_t GetTimeSinceEpochInSeconds() { return (uint32_t) std::chrono::duration_cast<second>(clock::now().time_since_epoch()).count(); }

private:
    typedef std::chrono::high_resolution_clock clock; // QueryPerformanceCounter
    typedef std::chrono::duration<float, std::ratio<1>> second;
    std::chrono::time_point<clock> begin;
};