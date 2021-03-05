/*
  ==============================================================================

    LFOComponent.cpp
    Created: 3 Mar 2021 8:54:26pm
    Author:  Seth Gory

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LFOComponent.h"

//==============================================================================
LFOComponent::LFOComponent()
{
    // Labels
    float font = 17.0f;
    addAndMakeVisible (sectionHeading);
    sectionHeading.setText ("LFO", juce::dontSendNotification);
    sectionHeading.setLookAndFeel (&customLAF);
    sectionHeading.setJustificationType (juce::Justification::centred);
    sectionHeading.setFont (font);
    
    addAndMakeVisible (rateLabel);
    rateLabel.setText ("rate", juce::dontSendNotification);
    rateLabel.setLookAndFeel (&customLAF);
    rateLabel.setJustificationType (juce::Justification::centred);
    rateLabel.setFont (font);
    
    addAndMakeVisible (depthLabel);
    depthLabel.setText ("depth", juce::dontSendNotification);
    depthLabel.setLookAndFeel (&customLAF);
    depthLabel.setJustificationType (juce::Justification::centred);
    depthLabel.setFont (font);
    
    // LFO Controls
    addAndMakeVisible (lfoRateSlider);
    lfoRateSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    lfoRateSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    lfoRateSlider.setLookAndFeel (&customLAF);
    
    addAndMakeVisible (lfoDepthSlider);
    lfoDepthSlider.setTextBoxStyle (juce::Slider::NoTextBox, true, 0, 0);
    lfoDepthSlider.setSliderStyle (juce::Slider::RotaryVerticalDrag);
    lfoDepthSlider.setLookAndFeel (&customLAF);
}

LFOComponent::~LFOComponent()
{
}

void LFOComponent::paint (juce::Graphics& g)
{
    g.setColour (juce::Colour (255, 210, 210));
    auto area = getLocalBounds();
    g.drawRoundedRectangle (area.toFloat().reduced(3), 10, 1);
}

void LFOComponent::resized()
{
    int reducedAmount = 10;
    auto area = getLocalBounds().reduced (reducedAmount);
    auto headingYOffset = getHeight() * 0.15;
    sectionHeading.setBounds (area.removeFromTop (headingYOffset));
    
    auto labelYOffset = headingYOffset;
    auto labelRow = area.removeFromTop (labelYOffset);
    auto halfWidth = (getWidth() - reducedAmount * 2) / 2;
    rateLabel.setBounds (labelRow.removeFromLeft (halfWidth));
    depthLabel.setBounds (labelRow.removeFromLeft (halfWidth));
    
    lfoRateSlider.setBounds (area.removeFromLeft ((getWidth() - reducedAmount * 2) / 2));
    lfoDepthSlider.setBounds (area);
    
}
