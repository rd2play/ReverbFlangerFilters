/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CombFilterAudioProcessor::CombFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

CombFilterAudioProcessor::~CombFilterAudioProcessor()
{
}

//==============================================================================
const juce::String CombFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool CombFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool CombFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool CombFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double CombFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int CombFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int CombFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void CombFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String CombFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void CombFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void CombFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    for (auto& flanger : cfeffect) 
    {
      flanger.setSampleRate(sampleRate);
    }
}

void CombFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CombFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void CombFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    auto d = apvts.getRawParameterValue("DEPTH");
    auto bd = apvts.getRawParameterValue("BASEDELAY");
    auto lfo = apvts.getRawParameterValue("LFO");

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //d->load()
    for (auto& flanger : cfeffect) {
        flanger.setBaseDelay(*bd);
        flanger.setDepth(*d);
        flanger.setLFORate(*lfo);
    }
    //auto leftChannelData = buffer.getWritePointer(0);
    //auto rightChannelData = buffer.getWritePointer(1);

    for (auto i = 0; i < buffer.getNumChannels(); ++i){
        auto channelData = buffer.getWritePointer(i);;
        for (auto frame = 0; frame < buffer.getNumSamples(); ++frame) {
           channelData[frame] = cfeffect[i].process(channelData[frame]);
           //rightChannelData[frame] = cfeffect[1].process(rightChannelData[frame]);
        }
    }


}

//==============================================================================
bool CombFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* CombFilterAudioProcessor::createEditor()
{
    return new CombFilterAudioProcessorEditor (*this);
}

//==============================================================================
void CombFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void CombFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CombFilterAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout CombFilterAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // [-1, 1]: input signal amplitude range
    // [0, 1]: gain range
    // 0.5 * ([-1, 1] + 1 * [-1, 1]) = 0.5 * [-2, 2] = [-1, 1]
    // y[n] = 0.5 * (x[n] + gain * x[n - delay])
    //first two are in ms
    params.push_back(std::make_unique<juce::AudioParameterFloat>("DEPTH", "Depth", 0.f, 2.f, 1.f));
    params.push_back(std::make_unique<juce::AudioParameterInt>("BASEDELAY", "Base Delay", 0.f, 15.f, 10.f));
    // in Hz
    params.push_back(std::make_unique<juce::AudioParameterFloat>("LFO", "LFO", 0.0f, 1.0f, 0.25f));

    return { params.begin(), params.end() };
}
