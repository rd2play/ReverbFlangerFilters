/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
CombFilterAudioProcessorEditor::CombFilterAudioProcessorEditor (CombFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    depthslider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthslider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(depthslider);
    depthLabel.setText("Depth [ms]", juce::dontSendNotification);
    depthLabel.attachToComponent(&depthslider, false);
    depthSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "DEPTH", depthslider);


    basedelayslider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    basedelayslider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(basedelayslider);
    baseDelayLabel.setText("Base delay[ms]", juce::dontSendNotification);
    baseDelayLabel.attachToComponent(&basedelayslider, false);
    baseDelaySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "BASEDELAY", basedelayslider);

	lforateslider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	lforateslider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 50);
    addAndMakeVisible(lforateslider);
    lfoRateLabel.setText("LFO [Hz]", juce::dontSendNotification);
    lfoRateLabel.attachToComponent(&lforateslider, false);
	lfoRateSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "LFO", lforateslider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

CombFilterAudioProcessorEditor::~CombFilterAudioProcessorEditor()
{
}

//==============================================================================
void CombFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Schroeder Reverb", getLocalBounds(), juce::Justification::centredTop, 1);
}

void CombFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    //depthLabel.setBounds(getWidth() / 2 - 200, getHeight() / 1.5 - 100, 100, 100);
    depthslider.setBounds(getWidth() / 2 - 200, getHeight() / 2 - 100, 100, 100);
    basedelayslider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 100, 100, 100);
    lforateslider.setBounds(getWidth() / 2, getHeight() / 2 - 100, 100, 100);
}
