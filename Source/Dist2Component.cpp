/*
  ==============================================================================

    Dist2Component.cpp
    Created: 3 Mar 2021 10:23:14pm
    Author:  Seth Gory

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Dist2Component.h"

//==============================================================================
Dist2Component::Dist2Component(TremDistortionAudioProcessor& p)
: audioProcessor (p)
{
    // Control knobs
    addAndMakeVisible (gainSlider);
    gainSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setLookAndFeel (&customLAF);
    
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN2", gainSlider);
    
    addAndMakeVisible (toneSlider);
    toneSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    toneSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    toneSlider.setLookAndFeel (&customLAF);
    
    toneSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "TONE2", toneSlider);
    
    addAndMakeVisible (volSlider);
    volSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    volSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    volSlider.setLookAndFeel (&customLAF);
    
    volSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "VOL2", volSlider);
    
    // Labels
    float font = 17.0f;
    addAndMakeVisible (sectionHeading);
    sectionHeading.setText ("TANH", juce::dontSendNotification);
    sectionHeading.setLookAndFeel (&customLAF);
    sectionHeading.setJustificationType (juce::Justification::centred);
    sectionHeading.setFont (font);
    
    addAndMakeVisible (gainLabel);
    gainLabel.setText ("gain", juce::dontSendNotification);
    gainLabel.setLookAndFeel (&customLAF);
    gainLabel.setJustificationType (juce::Justification::centred);
    gainLabel.setFont (font);
    
    addAndMakeVisible (toneLabel);
    toneLabel.setText ("lpf", juce::dontSendNotification);
    toneLabel.setLookAndFeel (&customLAF);
    toneLabel.setJustificationType (juce::Justification::centred);
    toneLabel.setFont (font);
    
    addAndMakeVisible (volLabel);
    volLabel.setText ("vol", juce::dontSendNotification);
    volLabel.setLookAndFeel (&customLAF);
    volLabel.setJustificationType (juce::Justification::centred);
    volLabel.setFont (font);
}

Dist2Component::~Dist2Component()
{
}

void Dist2Component::paint (juce::Graphics& g)
{
    g.setColour (juce::Colour (255, 210, 210));
    auto area = getLocalBounds();
    g.drawRoundedRectangle (area.toFloat().reduced(3), 10, 1);
}

void Dist2Component::resized()
{
    int reducedAmount = 10;
    auto area = getLocalBounds().reduced (reducedAmount);
    auto headingYOffset = getHeight() * 0.15;
    sectionHeading.setBounds (area.removeFromTop (headingYOffset));
    
    auto labelYOffset = headingYOffset;
    auto labelRow = area.removeFromTop (labelYOffset);
    auto thirdWidth = (getWidth() - reducedAmount * 2) / 3;
    gainLabel.setBounds (labelRow.removeFromLeft (thirdWidth));
    toneLabel.setBounds (labelRow.removeFromLeft (thirdWidth));
    volLabel.setBounds (labelRow);
    
    gainSlider.setBounds (area.removeFromLeft (thirdWidth));
    toneSlider.setBounds (area.removeFromLeft (thirdWidth));
    volSlider.setBounds (area);
}
