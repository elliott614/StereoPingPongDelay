/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "fxobjects.h"

//==============================================================================
/**
*/
class StereoPingPongDelayAudioProcessor  : public juce::AudioProcessor
{
public:
    // --- Continuous Plugin Variables 
    double delayTime_mSec = 0.0;
    double delayFeedback_Pct = 0.0;
    double delayRatio_Pct = 0.0;
    double wetLevel_dB = 0.0;
    double dryLevel_dB = 0.0;

    // --- Discrete Plugin Variables 
    int delayType = 0;
    delayAlgorithm delayAlg = delayAlgorithm::kNormal;	// to compare: if(compareEnumToInt(delayTypeEnum::normal, delayType)) etc...


    //==============================================================================
    StereoPingPongDelayAudioProcessor();
    ~StereoPingPongDelayAudioProcessor() override;
    float leftPercent = 0.;
    float rightPercent = 0.;
    AudioDelay audioDelayObject;
    AudioDelayParameters delayParams;
    float inputSamples[2];
    float outputSamples[2];
    float* channelData[2];

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void updateParameters();
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoPingPongDelayAudioProcessor)

 
};
