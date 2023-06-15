#pragma once
#include "DelayLine.h"

namespace CF {
    class FeedBackFilter {
    public:        
        void process(float* samples, int samplesCount);
        void setDelay(int newDelay) { this->delay = newDelay; }
        void setGain(float newGain) { this->gain = newGain; }

    private:
        DL::DelayLine delayLine{};
        int delay;
        float gain;
    };
}