#include "Flanger.h"

namespace {
/**
* lfoValue in [-1, 1]
* @return value in [baseValue - depth, baseValue + depth] range
*/
float modulateBipolar(float baseValue, float depth, float lfoValue) {
  return baseValue + depth * lfoValue;
}

/**
* lfoValue in [-1, 1]
* @return value in [baseValue, baseValue + depth] range
*/
float modulateUnipolar(float baseValue, float depth, float lfoValue) {
  const auto unipolarLFOValue = (lfoValue + 1.f) / 2.f;  // in [0, 1] range
  return baseValue + depth * unipolarLFOValue;
}
}

namespace CF {

    void Flanger::setSampleRate(float sampleRate) {
      _sampleRate = sampleRate;      
      _lfo.setSampleRate(sampleRate);
      // Values according to Digital Audio FX (2011 edition)
      _combFilter.setFeedbackCoefficient(0.7f);
      _combFilter.setFeedforwardCoefficient(0.7f);
      _combFilter.setBlend(0.7f);
    }

    float Flanger::process(float sample) {
      const auto lfoValue = _lfo.getNextSample();
      // Example: _baseDelay = 1; _depth = 3; lfoValue in [-1, 1]; currentDelay in [-2, 4] (bipolar modulation);
      // In bipolar modulation, currentDelay in [_baseDelay - _depth, _baseDelay + _depth]; (_baseDelay is midpoint, depth is halfrange)
      // In unipolar modulation, currentDelay in [_baseDelay, _baseDelay + _depth].
      const auto currentDelay = modulateUnipolar(_baseDelay, _depth, lfoValue);
      _combFilter.setDelay(currentDelay);
      _combFilter.process(&sample, 1);
      return sample;
    }

}  // namespace CF
