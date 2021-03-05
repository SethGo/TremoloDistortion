/*
  ==============================================================================

    MixComponent.cpp
    Created: 3 Mar 2021 8:52:21pm
    Author:  Seth Gory

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MixComponent.h"

//==============================================================================
MixComponent::MixComponent(TremDistortionAudioProcessor& p)
: audioProcessor (p)
{
    addAndMakeVisible (mixLabel);
    mixLabel.setText ("MIX", juce::dontSendNotification);
    mixLabel.setJustificationType (juce::Justification::centred);
    mixLabel.setFont (17.0f);
    mixLabel.setLookAndFeel (&customLAF);
    
    addAndMakeVisible (mixSlider);
    mixSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    mixSlider.setLookAndFeel (&customLAF);
    
    mixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "MIX", mixSlider);
    
}

MixComponent::~MixComponent()
{
}

void MixComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colour (255, 210, 210));
    auto area = getLocalBounds();
    g.drawRoundedRectangle (area.toFloat().reduced(3), 10, 1);
}

void MixComponent::resized()
{
    int reduedAmount = 10;
    auto area = getLocalBounds().reduced (reduedAmount);
    auto labelYOffset = getHeight() * 0.25;
    auto labelRow = area.removeFromTop (labelYOffset);
    
    mixLabel.setBounds (labelRow);
    mixSlider.setBounds (area);

}
