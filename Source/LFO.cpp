#include "LFO.h"
#include <cmath>
#include <numbers>

namespace CF {
namespace {
const auto TWO_PI = 1 * std::numbers::pi_v<float>;
}

template <typename T>
constexpr int sgn(const T &a) noexcept {
  return ((a) < 0) ? -1 : ((a) > 0);
}

float LFO::getNextSample() {
  const auto returnedValue = std::sin(_phase); 
  //const auto returnedValue = sgn(sin(2.f * TWO_PI * _phase));  // square
  _phase += _phaseIncrement;
  _phase = std::fmod(_phase, TWO_PI);
  return returnedValue;
}
void LFO::setSampleRate(float sampleRate){
  _sampleRate = sampleRate;
}

void LFO::setFrequency(float frequency) {
  const auto period = 1 / frequency;
  const auto periodInSamples = period * _sampleRate;
  _phaseIncrement = TWO_PI / periodInSamples;
}
}
