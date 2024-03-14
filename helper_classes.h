#ifndef HELPER_CLASSES_H
#define HELPER_CLASSES_H

#include <random> // for std::mt19937
#include <ctime> // for std::time

#include <algorithm> // for std::sort
#include <chrono> // for std::chrono functions
#include <cstddef> // for std::size_t
#include <numeric> // for std::iota
#include <string>
#include <limits>

class Random {
private:
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };

public: 
    int get_int(int min, int max) {
        std::uniform_int_distribution<int> die{ min, max }; // we can create a distribution in any function that needs it
        return die(mersenne); // and then generate a random number from our global generator
    }
};

class Timer {
private:
    // Type aliases to make accessing nested type easier
    using clock_type = std::chrono::steady_clock;
    using second_type = std::chrono::duration<double, std::ratio<1> >;
    std::chrono::time_point<clock_type> m_beg{ clock_type::now() };

public:
    void reset() { m_beg = clock_type::now(); }
    double elapsed() const {
        return std::chrono::duration_cast<second_type>(clock_type::now() - m_beg).count();
    }
};

#endif