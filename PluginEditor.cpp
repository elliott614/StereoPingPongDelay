/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

void NewProjectAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    audioProcessor.delayTime_mSec = delayTimeSlider.getValue();
    audioProcessor.delayAlg = DelayTypeSlider.getValue() == 0 ? delayAlgorithm::kNormal : delayAlgorithm::kPingPong;
    audioProcessor.delayType = DelayTypeSlider.getValue();
    audioProcessor.delayFeedback_Pct = feedbackSlider.getValue();
    audioProcessor.delayRatio_Pct = ratioPercentSlider.getValue();
    audioProcessor.dryLevel_dB = dryDBSlider.getValue();
    audioProcessor.wetLevel_dB = wetDBSlider.getValue();
\
}

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (50, 30);
    delayTimeSlider.setSliderStyle (juce::Slider::LinearVertical);
    delayTimeSlider.setRange (0.0, 2000., 0.01);
    delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    delayTimeSlider.setPopupDisplayEnabled(true, false, this);
    delayTimeSlider.setTextValueSuffix("Delay Time (ms)");
    delayTimeSlider.setValue(0);
    addAndMakeVisible (&delayTimeSlider);
    delayTimeSlider.addListener (this);

    setSize(50, 30);
    DelayTypeSlider.setSliderStyle(juce::Slider::LinearVertical);
    DelayTypeSlider.setRange(0, 1, 1);
    DelayTypeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    DelayTypeSlider.setPopupDisplayEnabled(true, false, this);
    DelayTypeSlider.setTextValueSuffix("0=Normal, 1=PingPong");
    DelayTypeSlider.setValue(0);
    addAndMakeVisible(&DelayTypeSlider);
    DelayTypeSlider.addListener(this);

    setSize(50, 30);
    feedbackSlider.setSliderStyle(juce::Slider::LinearVertical);
    feedbackSlider.setRange(0., 100., .5);
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    feedbackSlider.setPopupDisplayEnabled(true, false, this);
    feedbackSlider.setTextValueSuffix("Feedback");
    feedbackSlider.setValue(0);
    addAndMakeVisible(&feedbackSlider);
    feedbackSlider.addListener(this);

    setSize(50, 30);
    ratioPercentSlider.setSliderStyle(juce::Slider::LinearVertical);
    ratioPercentSlider.setRange(0., 100., .5);
    ratioPercentSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    ratioPercentSlider.setPopupDisplayEnabled(true, false, this);
    ratioPercentSlider.setTextValueSuffix("% Ratio");
    ratioPercentSlider.setValue(0);
    addAndMakeVisible(&ratioPercentSlider);
    ratioPercentSlider.addListener(this);

    setSize(50, 30);
    dryDBSlider.setSliderStyle(juce::Slider::LinearVertical);
    dryDBSlider.setRange(-60., 3., .5);
    dryDBSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    dryDBSlider.setPopupDisplayEnabled(true, false, this);
    dryDBSlider.setTextValueSuffix("Dry Mix (dB)");
    dryDBSlider.setValue(0);
    addAndMakeVisible(&dryDBSlider);
    dryDBSlider.addListener(this);

    setSize(50, 30);
    wetDBSlider.setSliderStyle(juce::Slider::LinearVertical);
    wetDBSlider.setRange(-60., 3., .5);
    wetDBSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    wetDBSlider.setPopupDisplayEnabled(true, false, this);
    wetDBSlider.setTextValueSuffix("Wet Mix (dB)");
    wetDBSlider.setValue(0);
    addAndMakeVisible(&wetDBSlider);
    wetDBSlider.addListener(this);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // fill the whole window white
    g.fillAll(juce::Colours::white);

    // set the current drawing colour to black
    g.setColour(juce::Colours::black);

    // set the font size and draw text to the screen
    g.setFont(15.0f);

    g.drawFittedText("Delay", 0, 0, getWidth(), 30, juce::Justification::centred, 1);
}

void NewProjectAudioProcessorEditor::resized()
{
    delayTimeSlider.setBounds(40, 30, 20, getHeight() - 60);
    DelayTypeSlider.setBounds(60, 30, 20, getHeight() - 60);
    feedbackSlider.setBounds(80, 30, 20, getHeight() - 60);
    ratioPercentSlider.setBounds(100, 30, 20, getHeight() - 60);
    dryDBSlider.setBounds(120, 30, 20, getHeight() - 60);
    wetDBSlider.setBounds(140, 30, 20, getHeight() - 60);
}
