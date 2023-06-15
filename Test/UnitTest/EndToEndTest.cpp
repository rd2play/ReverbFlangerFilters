#include "gtest/gtest.h"
#include "AudioFile.h"
#include "Flanger.h"

TEST(Flanger, EndToEnd) {
	constexpr auto testtrack = "C:/JUCEProjects/CombFilter/Test/UnitTest/GuitarTrack.wav";

	AudioFile<float>::AudioBuffer buffer;
	AudioFile<float> audioFile;
	audioFile.load(testtrack);
	//ASSERT_EQ(audioFile.getNumSamplesPerChannel(), 1167144);
	//ASSERT_EQ(audioFile.getNumChannels(), 1);

	auto bitDepth = audioFile.getBitDepth();
	auto numChannels = audioFile.getNumChannels();
	auto numSamplesPerChannel = audioFile.getNumSamplesPerChannel();
	auto sampleRate = audioFile.getSampleRate();

	buffer.resize(1);
	buffer[0].resize(numSamplesPerChannel);
	//buffer[1].resize(numSamplesPerChannel);

	std::array<CF::Flanger, 1> cfeffect;
	for (auto& flanger : cfeffect)
	{
		flanger.setSampleRate(sampleRate);
		flanger.setBaseDelay(0.2f);		
		flanger.setDepth(0.0001f);
	}
	for (int i = 0; i < numSamplesPerChannel; i++)
	{
		auto currentSample = audioFile.samples[0][i];
		
		//for (int channel = 0; channel < numChannels; channel++)
		//{
			auto leftChannelData = cfeffect[0].process(currentSample);
			buffer[0][i] = leftChannelData;
		//}			
	}
	bool ok = audioFile.setAudioBuffer(buffer);

	// Set both the number of channels and number of samples per channel
	audioFile.setAudioBufferSize(numChannels, numSamplesPerChannel);

	// Set the number of samples per channel
	audioFile.setNumSamplesPerChannel(numSamplesPerChannel);

	// Set the number of channels
	audioFile.setNumChannels(numChannels);
	
	audioFile.setBitDepth(bitDepth);
	audioFile.setSampleRate(sampleRate);


	audioFile.save("C:/JUCEProjects/CombFilter/Test/UnitTest/audioFile.wav", AudioFileFormat::Wave);

}
