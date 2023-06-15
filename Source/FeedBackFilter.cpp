#include "FeedBackFilter.h"

namespace CF {

    void FeedBackFilter::process(float* samples, int samplesCount)
    {        
        delayLine.setDelay(delay);

        for (int i = 0; i < samplesCount; i++)
        {
            // process phase
            const auto delayedSample = delayLine.popSample();            
            const auto outputSample = 0.5f * ((gain * delayedSample) + samples[i]);
            samples[i] = outputSample;
            
            // state update phase
            delayLine.pushSample(outputSample);
        }
    }
}
