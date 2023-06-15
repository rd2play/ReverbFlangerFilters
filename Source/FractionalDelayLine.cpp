#include <algorithm>
#include <array>
#include <vector>
#include <cmath>
#include <cassert>
#include "FractionalDelayLine.h"

using namespace std;

namespace DL {

    float FractionalDelayLine::popSample() {
        assert(delay >= 0.f);
        assert(delay < static_cast<float>(buffer.size()));
        auto readHead = writeHead - 1 - delay;
        if (readHead < 0) {
        readHead += std::ssize(buffer);
        }
        auto truncatedReadHead = static_cast<int>(std::floor(readHead));
        auto truncatedReadHeadPlusOne = truncatedReadHead + 1; 
        const auto truncatedReadHeadWeight =
            std::abs(readHead - truncatedReadHeadPlusOne);
        const auto truncatedReadHeadPlusOneWeight =
            std::abs(readHead - truncatedReadHead);
        if (truncatedReadHeadPlusOne >= std::ssize(buffer)) {
        truncatedReadHeadPlusOne -= std::ssize(buffer);
        }
        assert(0 <= truncatedReadHead);
        assert(0 <= truncatedReadHeadPlusOne);
        assert(truncatedReadHead < std::ssize(buffer));
        assert(truncatedReadHeadPlusOne < std::ssize(buffer));
        const auto outputSample =
            truncatedReadHeadWeight * buffer[truncatedReadHead] +
            truncatedReadHeadPlusOneWeight * buffer[truncatedReadHeadPlusOne];
        return outputSample;
    }

    float FractionalDelayLine::popSampleNew() {
        int readHead = writeHead - 1 - static_cast<int>(delay);
        if (readHead < 0) {
	        readHead += std::ssize(buffer);
        }
        auto y1 = buffer[readHead];

        readHead = writeHead - 1 - (static_cast<int>(delay) + 1);
        if (readHead < 0) {
	        readHead += std::ssize(buffer);
        }
        auto y2 = buffer[readHead];

        float fraction = delay - static_cast<int>(delay);
        assert(fraction < 1.0f);

        const auto outputSample =
	        (fraction)*y2 + (1.0 - fraction) * y1;
        return outputSample;
    }

void FractionalDelayLine::pushSample(float inputSample) {
  buffer[writeHead] = inputSample;
  writeHead++;
  writeHead %= std::ssize(buffer);
}

void FractionalDelayLine::setDelay(float newDelay) {
  delay = newDelay;
}

}  // namespace DL
