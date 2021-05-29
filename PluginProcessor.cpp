/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessor::NewProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
    )

#endif
{
}

NewProjectAudioProcessor::~NewProjectAudioProcessor()
{
}

//==============================================================================
const juce::String NewProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NewProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NewProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NewProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NewProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NewProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NewProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NewProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void NewProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NewProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    audioDelayObject.reset(sampleRate);
    audioDelayObject.createDelayBuffers(sampleRate, 2000.0);
    delayParams.leftDelay_mSec = delayTime_mSec;
    delayParams.feedback_Pct = delayFeedback_Pct;
    delayParams.delayRatio_Pct = delayRatio_Pct;
    delayParams.updateType = delayUpdateType::kLeftPlusRatio;
    delayParams.dryLevel_dB = dryLevel_dB;
    delayParams.wetLevel_dB = wetLevel_dB;

    // --- use helper
    delayParams.algorithm = static_cast<delayAlgorithm>(delayType);

    // --- set them
    audioDelayObject.setParameters(delayParams);
}

//====update delay effect parameters====================
void NewProjectAudioProcessor::updateParameters()
{
    delayParams.leftDelay_mSec = delayTime_mSec;
    delayParams.feedback_Pct = delayFeedback_Pct;
    delayParams.delayRatio_Pct = delayRatio_Pct;
    delayParams.updateType = delayUpdateType::kLeftPlusRatio;
    delayParams.dryLevel_dB = dryLevel_dB;
    delayParams.wetLevel_dB = wetLevel_dB;

    // --- use helper
    delayParams.algorithm = convertIntToEnum(delayType, delayAlgorithm);

    // --- set them
    audioDelayObject.setParameters(delayParams);
}




void NewProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NewProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void NewProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{

    channelData[0] = buffer.getWritePointer(0);
    channelData[1] = buffer.getWritePointer(1);

    updateParameters();

    for (int i = 0; i < buffer.getNumSamples(); i++) //—2
    {
        for (int j = 0; j < 2; j++) {
            inputSamples[j] = channelData[j][i];
        }
        audioDelayObject.processAudioFrame(inputSamples, outputSamples, 2, 2);
        for (int j = 0; j < 2; j++) {
            channelData[j][i] = outputSamples[j];
        }
    }


}

//==============================================================================
bool NewProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NewProjectAudioProcessor::createEditor()
{
    return new NewProjectAudioProcessorEditor (*this);
}

//==============================================================================
void NewProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NewProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NewProjectAudioProcessor();
}
