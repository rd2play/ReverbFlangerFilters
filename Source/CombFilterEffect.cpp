#include "CombFilterEffect.h"

namespace CF {

	void CombFilterEffect::process(float* samples, int samplesCount)
	{

		gcFilter.process(samples, samplesCount);

		//for (int i = 0; i < samplesCount; i++)
		//{

		//	const auto combfiltersample = ffFilter.process(samples[i]);

		//	samples[i] = combfiltersample;

		//}


	};

	void CombFilterEffect::prepareToPlay(double /*sr*/, int /*samplesPerBlock*/)
	{
	
	};

	void CombFilterEffect::setFilterParameters(int channeldelay, float channelgain)
	{
                gcFilter.setDelay(channeldelay);  
				gcFilter.setFeedbackCoefficient(0.5f);
				gcFilter.setFeedforwardCoefficient(0.5f);
				gcFilter.setBlend(0.5f);
	}

}