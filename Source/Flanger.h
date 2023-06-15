#pragma once
#include "GeneralCombFilter.h"
#include "LFO.h"

namespace CF {

class Flanger {
 public:
  float process(float sample);
  void setSampleRate(float sampleRate);
  void setBaseDelay(float basedelayinMs) { _baseDelay = basedelayinMs * _sampleRate/1000.f; }
  void setDepth(float depthInMs) { _depth = depthInMs * _sampleRate / 1000.f; }
  void setLFORate(float lforate) { _lfo.setFrequency(lforate); }

 private:
  GeneralCombFilter _combFilter;
  LFO _lfo;
  float _baseDelay{0.f};
  float _sampleRate;
  float _depth = 0.f;
};
}  // namespace CF
