/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "fxobjects.h"

//==============================================================================
/**
*/
class StereoPingPongDelayAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                        private juce::Slider::Listener
{
public:
    StereoPingPongDelayAudioProcessorEditor (StereoPingPongDelayAudioProcessor&);
    ~StereoPingPongDelayAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(juce::Slider* slider) override;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    StereoPingPongDelayAudioProcessor& audioProcessor;
    juce::Slider delayTimeSlider;
    juce::Slider DelayTypeSlider;
    juce::Slider feedbackSlider;
    juce::Slider ratioPercentSlider;
    juce::Slider dryDBSlider;
    juce::Slider wetDBSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoPingPongDelayAudioProcessorEditor)
};
