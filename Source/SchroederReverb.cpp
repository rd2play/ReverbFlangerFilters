#include "SchroederReverb.h"
#include <algorithm>
#include <functional>

namespace SR {

    SchroederReverb::SchroederReverb() 
    {       

        setSampleRate(0.0f);
        setReverbTime(0.0f);

        allpassFilter1.setBlend(0.7f);
        allpassFilter1.setFeedforwardCoefficient(1);
        allpassFilter1.setFeedbackCoefficient(-0.7f);
        allpassFilter1.setDelay(347);

        allpassFilter2.setBlend(0.7f);
        allpassFilter2.setFeedforwardCoefficient(1);
        allpassFilter2.setFeedbackCoefficient(-0.7f);
        allpassFilter2.setDelay(113);

        allpassFilter3.setBlend(0.7f);
        allpassFilter3.setFeedforwardCoefficient(1);
        allpassFilter3.setFeedbackCoefficient(-0.7f);
        allpassFilter3.setDelay(37);

        feedbackFilter1.setBlend(0.4f);
        feedbackFilter1.setFeedforwardCoefficient(0);
        feedbackFilter1.setFeedbackCoefficient(0.773f);
        feedbackFilter1.setDelay(1687);

        feedbackFilter2.setBlend(0.4f);
        feedbackFilter2.setFeedforwardCoefficient(0);
        feedbackFilter2.setFeedbackCoefficient(0.802f);
        feedbackFilter2.setDelay(1601);

        feedbackFilter3.setBlend(0.4f);
        feedbackFilter3.setFeedforwardCoefficient(0);
        feedbackFilter3.setFeedbackCoefficient(0.753f);        
        feedbackFilter3.setDelay(2053);

        feedbackFilter4.setBlend(0.4f);
        feedbackFilter4.setFeedforwardCoefficient(0);
        feedbackFilter4.setFeedbackCoefficient(0.733f);
        feedbackFilter4.setDelay(2251);
    }

    void SchroederReverb::prepareToPlay(int samplesPerBlock, double sampleRate)
    {
        setSampleRate(sampleRate);        
        feedbackFilter1Input.resize(samplesPerBlock, 0);
        feedbackFilter2Input.resize(samplesPerBlock, 0);
        feedbackFilter3Input.resize(samplesPerBlock, 0);
        feedbackFilter4Input.resize(samplesPerBlock, 0);
    }

    float SchroederReverb::calculateFeedbackCoefficient(int delayTime)
    {        
        return exp((-3 * delayTime / sampleRate) / reverbTime);
    }

    void SchroederReverb::setReverbTime(float newReverbTime) {
        this->reverbTime = newReverbTime;
        feedbackFilter1.setFeedbackCoefficient(calculateFeedbackCoefficient(1687));
        feedbackFilter2.setFeedbackCoefficient(calculateFeedbackCoefficient(1601));
        feedbackFilter3.setFeedbackCoefficient(calculateFeedbackCoefficient(2053));
        feedbackFilter4.setFeedbackCoefficient(calculateFeedbackCoefficient(2251));
    }

    void SchroederReverb::process(float* samples, int samplesCount)
    {
        allpassFilter1.process(samples, samplesCount);
        allpassFilter2.process(samples, samplesCount);
        allpassFilter3.process(samples, samplesCount);
        
        std::copy_n(samples, samplesCount, feedbackFilter1Input.begin());
        std::copy_n(samples, samplesCount, feedbackFilter2Input.begin());
        std::copy_n(samples, samplesCount, feedbackFilter3Input.begin());
        std::copy_n(samples, samplesCount, feedbackFilter4Input.begin());

        feedbackFilter1.process(feedbackFilter1Input.data(), samplesCount);
        feedbackFilter2.process(feedbackFilter2Input.data(), samplesCount);
        feedbackFilter3.process(feedbackFilter3Input.data(), samplesCount);
        feedbackFilter4.process(feedbackFilter4Input.data(), samplesCount);

        std::copy_n(feedbackFilter1Input.begin(), samplesCount, samples);
        std::transform(feedbackFilter2Input.begin(),
                       feedbackFilter2Input.begin() + samplesCount, samples, samples,
                       std::plus<float>{});
        std::transform(feedbackFilter3Input.begin(),
                       feedbackFilter3Input.begin() + samplesCount, samples,
                       samples, std::plus<float>{});
        std::transform(feedbackFilter4Input.begin(),
                       feedbackFilter4Input.begin() + samplesCount, samples,
                       samples, std::plus<float>{});

    }

}