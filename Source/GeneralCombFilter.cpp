#include "GeneralCombFilter.h"

namespace CF {

    void GeneralCombFilter::process(float* samples, int samplesCount)
    {
        for (int i = 0; i < samplesCount; i++)
        {
            // process phase
            const auto delayedSample = delayLine.popSample();
            const auto delayLineInput = (feedbackCoefficient * delayedSample) + samples[i];

            const auto outputSample =
                delayLineInput * blend + feedforwardCoefficient * delayedSample;
            samples[i] = outputSample;

            // state update phase
            delayLine.pushSample(delayLineInput);
        }
    }
}