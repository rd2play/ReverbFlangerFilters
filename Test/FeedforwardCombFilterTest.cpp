// Compile with
// $ g++ FeedforwardCombFilterTest.cpp  -I ../Source
// or
// > cl .\FeedforwardCombFilterTest.cpp /I ../Source
// or
// > cl .\FeedforwardCombFilterTest.cpp ..\Source\DelayLine.cpp ..\Source\ffFilter.cpp /I ../Source /std:c++20
// include the feedforward filter header
#include "FeedForwardFilter.h"
#include <cmath>
#include <iostream>
#include <cassert>

constexpr auto M_PI = 3.141592653589793238462643383279502884L;

int main() {
    // instantiate the feedforward filter
    CF::FeedForwardFilter feedforwardFilter;
    std::array<float, 20> signal{};
    float rads = M_PI / 180;

    constexpr auto period = 10.f;
    constexpr auto frequency = 1.f / period;
    constexpr auto samplingRate = 1.f;
    constexpr auto amplitude = 1.0f;

    // generate a sine with the period of 10 samples
    for (int i = 0; i < std::ssize(signal); i++)
    {        
      signal[i] = amplitude * std::sin(2 * M_PI * frequency *
                                       static_cast<float>(i) / samplingRate);
        //std::cout << signal[i] << std::endl;
    }


    // set the delay to 5 samples and gain to 1
    feedforwardFilter.setDelay(5);
    feedforwardFilter.setGain(1);
    
    // filter the sine
    for (int i = 0; i < std::ssize(signal); i++)
    {
        const auto combfiltersample = feedforwardFilter.process(signal[i]);
        signal[i] = combfiltersample;
    }

    // the output after the first half of the period should be all zeros
    for (int i = 5; i < std::ssize(signal); i++) {
        assert(std::abs(signal[i]) < 1e-7);
    }
}
