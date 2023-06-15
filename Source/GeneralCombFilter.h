#pragma once
#include "FractionalDelayLine.h"

namespace CF {
    class GeneralCombFilter {
    public:
        void process(float* samples, int samplesCount);
        void setDelay(float newDelay) { delayLine.setDelay(newDelay); }        
        void setFeedbackCoefficient(float newfbC) { this->feedbackCoefficient = newfbC; }
        void setFeedforwardCoefficient(float newffC) { this->feedforwardCoefficient = newffC; }
        void setBlend(float newBlend) { this->blend = newBlend; }
        
    private:
        DL::FractionalDelayLine delayLine{};
        float feedbackCoefficient;
        float blend;
        float feedforwardCoefficient;
    };
}
