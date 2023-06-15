/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class CombFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    CombFilterAudioProcessorEditor (CombFilterAudioProcessor&);
    ~CombFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider depthslider;
    juce::Slider basedelayslider;
    juce::Slider lforateslider;
    juce::Label  reverbLabel;
    juce::Label  depthLabel{"Depth [ms]"};
    juce::Label  baseDelayLabel{"Base delay [ms]"};
    juce::Label  lfoRateLabel{"LFO [Hz]"};
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> baseDelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lfoRateSliderAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    CombFilterAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CombFilterAudioProcessorEditor)
};
