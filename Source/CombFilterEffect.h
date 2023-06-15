#pragma once
#include "FeedForwardFilter.h"
#include "FeedBackFilter.h"
#include "GeneralCombFilter.h"

namespace CF {

    class CombFilterEffect{
    public: 
        void process(float* samples, int samplesCount);
		void prepareToPlay(double sampleRate, int samplesPerBlock);
        void setFilterParameters(int delay, float gain);

    private:
        FeedForwardFilter ffFilter;
        FeedBackFilter fbFilter;
        GeneralCombFilter gcFilter;

    };
}
