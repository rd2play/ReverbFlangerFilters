#pragma once
#include "GeneralCombFilter.h"
#include <vector>

namespace SR {
	class SchroederReverb {
	public:
		void process(float* samples, int samplesCount);
		SchroederReverb();
		void prepareToPlay(int samplerPerBlock, double dawSampleRate);
		void setSampleRate(float newSampleRate) { this->sampleRate = newSampleRate; }
        void setReverbTime(float newReverbTime);
		float calculateFeedbackCoefficient(int delayTime);

	private:
		CF::GeneralCombFilter allpassFilter1;
		CF::GeneralCombFilter allpassFilter2;
		CF::GeneralCombFilter allpassFilter3;
		CF::GeneralCombFilter feedbackFilter1;
		CF::GeneralCombFilter feedbackFilter2;
		CF::GeneralCombFilter feedbackFilter3;
		CF::GeneralCombFilter feedbackFilter4;
		std::vector<float> feedbackFilter1Input;
		std::vector<float> feedbackFilter2Input;
		std::vector<float> feedbackFilter3Input;
		std::vector<float> feedbackFilter4Input;
		float sampleRate;	
		float reverbTime;

	};
}