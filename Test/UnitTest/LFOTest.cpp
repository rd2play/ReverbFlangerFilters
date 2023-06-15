#include "gtest/gtest.h"
#include "LFO.h"
#include <chrono>
#include "AudioFile.h"

TEST(LFO, Generate) {  
	using namespace std::chrono_literals;
	CF::LFO _lfo;

	_lfo.setSampleRate(44100.f);
	_lfo.setFrequency(1.f);	
	constexpr auto lengthinseconds = 5s;	
	constexpr auto lengthinsamples = 44100 * lengthinseconds.count();

	AudioFile<float>::AudioBuffer buffer;
	AudioFile<float> audioFile;

	buffer.resize(1);	
	buffer[0].resize(lengthinsamples);

	for (int i = 0; i < lengthinsamples; i++) {
		const auto lfoValue = _lfo.getNextSample();
          buffer[0][i] = lfoValue;
          
	}
	bool ok = audioFile.setAudioBuffer(buffer);

	audioFile.save("C:/JUCEProjects/CombFilter/Test/UnitTest/lfoFile.wav", AudioFileFormat::Wave);

}
